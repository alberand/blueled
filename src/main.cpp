#include <stdio.h>
#include <stdarg.h>

#include <avr/interrupt.h>
#include <Arduino.h>
#include <EEPROM.h>
#include <FastLED.h>
#include <ledfx.h>

#include "simpap.hpp"
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
#define PIN_HEARTBEAT PB1
#define CYCLE_MAX_DURATION 100

// Communication
#define COMMAND_OFFSET 0
#define PARAMS_NUM_OFFSET 2
#define PAYLOAD_OFFSET 3
#define MAX_PARAMS 20

// In updates per second (Hz)
#define BASE_FREQ 100
#define BASE_PERIOD (1000/BASE_FREQ)

// Constants for saving application state to memory
#define MEM_BASE_ADDRESS 0x0
#define MEM_NEW_STATE_ADDRESS (MEM_BASE_ADDRESS + 0x0)
#define MEM_STATE_ADDRESS (MEM_NEW_STATE_ADDRESS + sizeof(bool))
#define MEM_ANIMATION_STATE_ADDRESS (MEM_STATE_ADDRESS + sizeof(state))
#define MEM_ANIMATION_PARAMS_ADDRESS (MEM_ANIMATION_STATE_ADDRESS + sizeof(ledfx_state))

#define MAX_LEDS 256

#define START_COMM 0xAA
#define ACK 0xBB
#define COMM_INIT_MSG 0x20
#define COMM_SET_BRIGHT_MSG 0x21

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

    bool valid_id = false;
    for(uint8_t i = 0; i < CONFIGS_SIZE; i++){
        if(state_t->animation == configs[i]->id){
            valid_id = true;
        }
    }
    if(!valid_id){
        return false;
    }

    if(state_t->config == NULL){
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

    uint16_t cmd = get_u16((data + COMMAND_OFFSET));

    // Init packet (set number of leds)
    if(cmd == COMM_INIT_MSG) {
        // digitalWrite(LED_BUILTIN, HIGH);
        NUM_LEDS = (uint16_t)get_u32((data + PAYLOAD_OFFSET));

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
    if(true) {
        /* Apply animation */
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i]->id != cmd) {
                continue;
            }

            state_t.animation = configs[i]->id;
            state_t.config = configs[i];
            ledfx_state_reset();

            uint8_t params_num = get_u8(data + PARAMS_NUM_OFFSET);
            ledfx_set_total_params(params_num);
            for(uint8_t i = 0; i < params_num; i++){
                uint32_t value = get_u32((data + PAYLOAD_OFFSET + i*sizeof(uint32_t)));
                ledfx_set_param(i, value);
            }

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

    ledfx_effect(state_t->animation, leds, state_t->num_leds);
    return true;
}

void state_save(const struct state* state_t)
{
    if(!state_check(state_t)){
        return;
    }

    EEPROM.put(MEM_STATE_ADDRESS, *state_t);
    EEPROM.put(MEM_ANIMATION_STATE_ADDRESS, animation_t);
    for(int i = 0; i < state_t->config->num; i++) {
        uint32_t address = MEM_ANIMATION_PARAMS_ADDRESS + sizeof(uint32_t)*i;
        EEPROM.put(address, animation_t.params[i]);
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
        EEPROM.get(MEM_ANIMATION_STATE_ADDRESS, animation_t);

        // Assign config based on state_t->animation
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i]->id != state_t->animation) {
                continue;
            }

            state_t->config = configs[i];
        }

        // Read config params
        animation_t.params = (uint32_t*)malloc(state_t->config->num*sizeof(uint32_t));
        for(int i = 0; i < state_t->config->num; i++) {
            uint32_t address = MEM_ANIMATION_PARAMS_ADDRESS + sizeof(uint32_t)*i;
            EEPROM.get(address, animation_t.params[i]);
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
    state_t->brightness = 0xFF;
    state_t->animation = 0x44;
    state_t->config = configs[3];
    ledfx_state_reset();
}

void setup()
{
    Serial.begin(115200, SERIAL_8E1);
    while (!Serial) { ; }
    Serial.flush();

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_RESET, INPUT);
    pinMode(PIN_DEBUG, OUTPUT);
    pinMode(PIN_HEARTBEAT, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_DEBUG, LOW);
    digitalWrite(PIN_HEARTBEAT, HIGH);

    // Configure LED strip
    set_max_power_in_volts_and_milliamps(MAX_VOLTS, MAX_AMPS*1000);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, MAX_LEDS);

    simpap_init(&simpap_ctx);

    ledfx_init();

    // Read configuration from EEPROM if exist
    if(digitalRead(PIN_RESET) || !state_load(&state_t)) {
        // Initial state - Rainbow
        simpap_send(&simpap_ctx, (uint8_t*)"load failed", 11);
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
    digitalWrite(PIN_HEARTBEAT, LOW);

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

    digitalWrite(PIN_HEARTBEAT, HIGH);
    stop = millis();
}
