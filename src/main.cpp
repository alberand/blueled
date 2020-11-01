#include <stdio.h>
#include <stdarg.h>

#include <avr/interrupt.h>
#include <Arduino.h>
#include <EEPROM.h>

#include "simpap.hpp"
#include "leds.hpp"
#include "common.hpp"

#define DEBUG

// Software-Hardoware configuration
// Always 5V
#define MAX_VOLTS 5
#define MAX_AMPS 5
// Therefore, 25 W in total

// Application related
#define DATA_PIN PD7
#define PIN_RESET PD3
#define PIN_DEBUG PB0
#define CYCLE_MAX_DURATION 100

// Communication
#define PAYLOAD_OFFSET 2
#define MAX_PARAMS 20

// In updates per second (Hz)
#define BASE_FREQ 100
#define BASE_PERIOD (1000/BASE_FREQ)

// Constants for saving application state to memory
#define MEM_BASE_ADDRESS 0x0
#define MEM_NEW_STATE_ADDRESS (MEM_BASE_ADDRESS + 0x0)
#define MEM_STATE_ADDRESS (MEM_NEW_STATE_ADDRESS + sizeof(bool))
#define MEM_PARAMS_ADDRESS (MEM_STATE_ADDRESS + sizeof(state))

#define MAX_LEDS 256

#define START_COMM 0xAA
#define ACK 0xBB
#define COMM_INIT_MSG 0x20
#define COMM_SET_BRIGHT_MSG 0x21
#define COMM_ANIM_FIRST (configs[0].id)
#define COMM_ANIM_LAST (configs[COUNT_OF(configs) - 1].id)

static bool in_comm = false;

// Define the array of leds
CRGB leds[MAX_LEDS];

uint16_t NUM_LEDS;

struct simpap simpap_ctx;
static uint16_t start, stop;

static struct state
{
    uint16_t iteration;
    uint16_t num_leds;
    uint8_t brightness;
    uint8_t animation;
    struct animation_config* config;
} state_t;

void simpap_send_char(uint8_t ch);
void simpap_handler(uint8_t* data, uint8_t len);

bool state_check(const struct state* state_t);
bool state_update(struct state* state_t);
void state_save(const struct state* state_t);
bool state_load(struct state* state_t);
void state_print(const struct state* state_t);
void state_reset(struct state* state_t);

void print(const char *__fmt, ...)
{
#ifdef DEBUG
    char buf[50] = { 0 };
    va_list va;
    va_start(va, __fmt);
    vsprintf(buf, __fmt, va);
    va_end(va);

    simpap_send(&simpap_ctx, (uint8_t*)buf, COUNT_OF(buf));
#endif
}

bool state_check(const struct state* state_t)
{
    if(state_t->num_leds > MAX_LEDS){
        return false;
    }

    if(state_t->animation < configs[0].id){
        return false;
    }

    if(state_t->animation > configs[COUNT_OF(configs) - 1].id){
        return false;
    }

    if(state_t->config == nullptr || state_t->config == NULL){
        return false;
    }

    return true;
}

void state_print(const struct state* state_t)
{
    // print("ok (anim: %X)", state_t->animation);
    simpap_send(&simpap_ctx, (uint8_t*)"ok (anim)", 9);
}

// SoftwareSerial toSlave(10, 11);
void simpap_send_char(uint8_t ch)
{
    Serial.write(ch);
}

void simpap_handler(uint8_t* data, uint8_t len)
{
    in_comm = false;
    simpap_send_char(ACK);

    uint16_t cmd = get_u16(data);

    // Init packet (set number of leds)
    if(cmd == COMM_INIT_MSG) {
        // digitalWrite(LED_BUILTIN, HIGH);
        NUM_LEDS = get_u16((data + PAYLOAD_OFFSET));

        if(NUM_LEDS > MAX_LEDS){
            return;
        }

        state_t.num_leds = NUM_LEDS;
        state_save(&state_t);

        return;
    }

    if(cmd == COMM_SET_BRIGHT_MSG) {
        uint32_t brightness = get_u32((data + PAYLOAD_OFFSET));

        if(brightness > 255){
            brightness = 255;
        }

        state_t.brightness = static_cast<uint8_t>(brightness);
        FastLED.setBrightness(state_t.brightness);

        state_save(&state_t);

        return;
    }

    // Set animation (animation with parameters)
    if(cmd >= COMM_ANIM_FIRST && cmd <= COMM_ANIM_LAST) {
        /* Apply animation */
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != cmd) {
                continue;
            }

            state_t.animation = configs[i].id;
            state_t.config = &configs[i];
            free(state_t.config->params);
            state_t.config->params = (uint32_t*)malloc(state_t.config->size*4);
            if(state_t.config->params != nullptr){
                memcpy((void*)state_t.config->params, data + PAYLOAD_OFFSET,
                   state_t.config->size*4);
            }

            animation_state_reset();
            state_save(&state_t);
        }

        return;
    }

    // unknown
    // print("nok (unknown msg)");
    simpap_send(&simpap_ctx, (uint8_t*)"nok (unknown msg)", 17);
}

bool state_update(struct state* state_t)
{
    state_t->iteration++;

    if(state_t->iteration%(state_t->config->delay/BASE_PERIOD) == 0) {
        animation_state_update(leds, state_t->num_leds, state_t->config);
        return true;
    }

    return false;
}

void state_save(const struct state* state_t)
{
    if(!state_check(state_t)){
        return;
    }

    EEPROM.put(MEM_STATE_ADDRESS, *state_t);
    for(int i = 0; i < state_t->config->size; i++) {
        EEPROM.put(MEM_PARAMS_ADDRESS + sizeof(state_t->config->params[0])*i,
                   state_t->config->params[i]);
    }
    // This flag is used only to check that config was saved
    bool state_new = true;
    EEPROM.put(MEM_NEW_STATE_ADDRESS, state_new);
}

bool state_load(struct state* state_t)
{
    // Check if config exist in memory
    bool is_config_new = false;
    if(EEPROM.get(MEM_NEW_STATE_ADDRESS, is_config_new)) {
        state_reset(state_t);
        EEPROM.get(MEM_STATE_ADDRESS, *state_t);

        // Assign config based on state_t->animation
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != state_t->animation) {
                continue;
            }

            state_t->config = &configs[i];
        }
        // Read config params
        state_t->config->params = (uint32_t*)malloc(state_t->config->size*4);
        for(int i = 0; i < state_t->config->size; i++) {
            EEPROM.get(MEM_PARAMS_ADDRESS + sizeof(state_t->config->params[0])*i,
                       state_t->config->params[i]);
        }
    }

    if(!state_check(state_t)) {
        // print("nok (fail mem read)");
        simpap_send(&simpap_ctx, (uint8_t*)"nok (fail mem read)", 19);
        return false;
    }

    return true;
}

void state_reset(struct state* state_t)
{
    state_t->iteration = 0;
    state_t->num_leds = 10;
    state_t->animation = 0x44;
    state_t->config = &configs[3];
    state_t->config->params = nullptr;
}

void setup()
{
    Serial.begin(9600, SERIAL_8E1);
    while (!Serial) { ; }
    Serial.flush();

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_RESET, INPUT);
    pinMode(PIN_DEBUG, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_DEBUG, LOW);

    // Configure LED strip
    set_max_power_in_volts_and_milliamps(MAX_VOLTS, MAX_AMPS*1000);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, MAX_LEDS);

    simpap_init(&simpap_ctx);

    // Read configuration from EEPROM if exist
    if(digitalRead(PIN_RESET) || !state_load(&state_t)) {
        // Initial state - Rainbow
        state_reset(&state_t);
        state_save(&state_t);
    }
}

void loop()
{
    if((stop - start) > CYCLE_MAX_DURATION) {
        // print("nok (overrun)");
        simpap_send(&simpap_ctx, (uint8_t*)"nok (overrun)", 13);
    }
    start = millis();

    // Receive input
    while (Serial.available()) {
        uint8_t ch = Serial.read();
        if(ch == START_COMM) {
            simpap_send_char(ACK);
            in_comm = true;
            continue;
        }
        if(in_comm){
            int8_t rc = simpap_accept_char(&simpap_ctx, ch);
            // Message is ok and handler was called
            if(rc == 1){
                break;;
            }
            // Parsing error or message is damaged
            if(rc != 0) {
                in_comm = false;
                simpap_send_char(ACK);
            }
        }
    }

    if(!in_comm) {
        if(state_update(&state_t)) {
            FastLED.setBrightness(state_t.brightness);
            FastLED.show();
        }
    }

    delay(BASE_PERIOD);

    stop = millis();
}
