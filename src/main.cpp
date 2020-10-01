#include <stdio.h>
#include <stdarg.h>

#include <avr/interrupt.h>
#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "simpap.hpp"
#include "leds.hpp"
#include "utils.hpp"
#include "common.hpp"

#include "config.hpp"

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

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

// In updates per second (Hz)
#define BASE_FREQ 100
#define BASE_PERIOD (1000/BASE_FREQ)

// Constants for saving application state to memory
#define MEM_BASE_ADDRESS 0x0
#define MEM_NEW_STATE_ADDRESS (MEM_BASE_ADDRESS + 0x0)
#define MEM_STATE_ADDRESS (MEM_NEW_STATE_ADDRESS + sizeof(bool))

#define MAX_LEDS 256

#define START_COMM 0xAA
#define ACK_START_COMM 0xBB

static bool in_comm = false;

// Define the array of leds
CRGB leds[MAX_LEDS];

uint16_t NUM_LEDS;

struct simpap simpap_ctx;
static uint16_t start, stop;

static struct state
{
    bool initialized;
    uint16_t iteration;
    uint16_t num_leds;
    uint8_t animation;
    const struct animation_config* config;
} state_t;

void simpap_send_char(uint8_t ch);
void simpap_handler(uint8_t* data, uint8_t len);

bool state_update(struct state* state_t);
void state_save(const struct state* state_t);
bool state_load(struct state* state_t);
void state_print(const struct state* state_t);
void state_reset(struct state* state_t);

void print(const char *__fmt, ...)
{
    char buf[100] = { 0 };
    va_list va;
    va_start(va, __fmt);
    vsprintf(buf, __fmt, va);
    va_end(va);

    simpap_send(&simpap_ctx, (uint8_t*)buf, sizeof(buf));
}

void state_print(const struct state* state_t)
{
    //print("[Debug] state_t.initialized: %s", state_t->initialized ? "true" : "false");
    //print("[Debug] state_t.iteration: %d", state_t->iteration);
    //print("[Debug] state_t.num_leds: %d", state_t->num_leds);
    print("[Debug] state_t.animation: %X", state_t->animation);
    // print("[Debug] state_t.config: %X", state_t->config);
    // printf("[Debug] state_t.config->id: %X", state_t->config->id);
    // printf("[Debug] state_t.config->delay: %d", state_t->config->delay);
}

// SoftwareSerial toSlave(10, 11);
void simpap_send_char(uint8_t ch)
{
    Serial.write(ch);
}

void simpap_handler(uint8_t* data, uint8_t len)
{
    uint16_t cmd = get_u16(data);

    /* Configuration commands. TODO make it more general if there is too many
     * of them */
    if(cmd == 0x20) {
        digitalWrite(LED_BUILTIN, HIGH);
        NUM_LEDS = get_u16((data + PAYLOAD_OFFSET));

        state_t.num_leds = NUM_LEDS;
        state_t.initialized = true;
        state_save(&state_t);
        print("init done");
    } else if(!state_t.initialized) {
        print("dunno LEDs");
    } else {
        digitalWrite(PIN_DEBUG, !digitalRead(PIN_DEBUG));
        /* Apply animation */
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != cmd) {
                continue;
            }

            print("change anim");
            state_t.animation = configs[i].id;
            state_t.config = &configs[i];
            animation_state_reset(state_t.config);
            state_save(&state_t);
            if(configs[i].payload_handler != NULL) {
                configs[i].payload_handler(&(data[PAYLOAD_OFFSET]),
                                           len - PAYLOAD_OFFSET);
            }
        }
    }
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
    print("save mem");
    state_print(state_t);
    EEPROM.put(MEM_STATE_ADDRESS, *state_t);
    // This flag is used only to check that config was saved
    bool state_new = true;
    EEPROM.put(MEM_NEW_STATE_ADDRESS, state_new);
}

bool state_load(struct state* state_t)
{
    bool is_config_new = false;
    if(EEPROM.get(MEM_NEW_STATE_ADDRESS, is_config_new)) {
        print("read mem");
        state_reset(state_t);
        EEPROM.get(MEM_STATE_ADDRESS, *state_t);
        state_print(state_t);

        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != state_t->animation) {
                continue;
            }

            state_t->config = &configs[i];
        }
    }

    // We don't read state from memory or:
    // state_t.animation shouldn't be zero as there is no animation
    // with id == 0
    if(state_t->animation == 0 or \
            state_t->animation > 0x60 or \
            state_t->num_leds > MAX_LEDS) {
        print("fail mem read");
        return false;
    }

    return true;
}

void state_reset(struct state* state_t)
{
    state_t->initialized = true;
    state_t->iteration = 0;
    state_t->num_leds = 10;
    state_t->animation = 0x44;
    state_t->config = &configs[3];
}

void setup()
{
    Serial.begin(9600, SERIAL_8E1);

    pinMode(LED_BUILTIN, OUTPUT);
    pinMode(PIN_RESET, INPUT);
    pinMode(PIN_DEBUG, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);
    digitalWrite(PIN_DEBUG, LOW);

    // Configure LED strip
    set_max_power_in_volts_and_milliamps(MAX_VOLTS, MAX_AMPS*1000);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, MAX_LEDS);

    simpap_init(&simpap_ctx);

    delay(1000);

    // Read configuration from EEPROM if exist
    if(digitalRead(PIN_RESET) || !state_load(&state_t)) {
        print("default anim");
        // Initial state - Rainbow
        state_reset(&state_t);
        state_save(&state_t);
    }
}

void loop()
{
    if((stop - start) > CYCLE_MAX_DURATION) {
        print("overrun");
    }
    start = millis();

    if(state_t.initialized && !in_comm) {
        if(state_update(&state_t)) {
            FastLED.show();
        }
    }

    delay(BASE_PERIOD);

    // Receive input
    while (Serial.available()) {
        uint8_t ch = Serial.read();
        if(ch == START_COMM) {
            print('%c', ACK_START_COMM);
            // in_comm = true;
            break;
            continue;
        }
        int8_t rc = simpap_accept_char(&simpap_ctx, ch);
        if(rc != 0) {
            print("failed char %d", rc);
            for(int i = 0; i < simpap_ctx.index; i++) {
                print("d: %X", simpap_ctx.buffer[i]);
            }
        } else {
            in_comm = false;
        }
    }

    stop = millis();
}
