#include <stdio.h>
#include <stdarg.h>

#include <Arduino.h>
#include <SoftwareSerial.h>
#include <EEPROM.h>

#include "simpap.hpp"
#include "leds.hpp"
#include "utils.hpp"
#include "common.hpp"

#include "config.hpp"

// Software-Hardoware configuration
// Always 5V
#define MAX_VOLTS 5
#define MAX_AMPS 5
// Therefore, 25 W in total

// Application related
#define DATA_PIN PD7
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

// Define the array of leds
CRGB* leds;

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

void state_update(struct state* state_t);
void state_save(const struct state* state_t);
bool state_load(struct state* state_t);
void state_print(struct state* state_t);
void state_reset(struct state* state_t);

void print(const char *__fmt, ...)
{
    char buf[50] = { 0 };
    va_list va;
    va_start(va, __fmt);
    vsprintf(buf, __fmt, va);
    va_end(va);

    simpap_send(&simpap_ctx, (uint8_t*)buf, sizeof(buf));
}

void state_print(struct state* state_t)
{
    print("[Debug] state_t.initialized: %s", state_t->initialized ? "true" : "false");
    print("[Debug] state_t.iteration: %d", state_t->iteration);
    print("[Debug] state_t.num_leds: %d", state_t->num_leds);
    print("[Debug] state_t.animation: %X", state_t->animation);
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
        if(leds != NULL) {
            free(leds);
        }
        NUM_LEDS = get_u16((data + PAYLOAD_OFFSET));
        leds = (CRGB*)malloc(NUM_LEDS*sizeof(CRGB));
        FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);
        state_t.num_leds = NUM_LEDS;
        state_t.initialized = true;
        state_save(&state_t);
        print("[Info] Initialization complete");
    } else if(!state_t.initialized) {
        print("[Error] Not known number of LEDs");
    } else {
        /* Apply animation */
        for(uint16_t i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != cmd) {
                continue;
            }

            print("[Info] Changing animation");
            state_t.animation = configs[i].id;
            state_t.config = &configs[i];
            state_save(&state_t);
            animation_state_reset(state_t.config);
            if(configs[i].payload_handler != NULL) {
                configs[i].payload_handler(&(data[PAYLOAD_OFFSET]),
                                           len - PAYLOAD_OFFSET);
            }
        }
    }
}

void state_update(struct state* state_t)
{
    state_t->iteration++;

    if(state_t->iteration%(state_t->config->delay/BASE_PERIOD) == 0) {
        animation_state_update(leds, state_t->num_leds, state_t->config);
    }
}

void state_save(const struct state* state_t)
{
    print("[Debug] Saving state");
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
        print("[Info] Reading configuration from EEPROM");
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
    if(state_t->animation == 0) {
        print("[Error] Failed to read app state from EEPROM");
        return false;
    }

    return true;
}

void state_reset(struct state* state_t)
{
    state_t->initialized = true;
    state_t->iteration = 0;
    state_t->num_leds = 10;
    state_t->animation = 0x4e;
    state_t->config = &configs[3];

    if(leds != NULL) {
        free(leds);
    }
    leds = (CRGB*)malloc(state_t->num_leds*sizeof(CRGB));
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, state_t->num_leds);
}

void setup()
{
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    // Configure LED strip
    set_max_power_in_volts_and_milliamps(MAX_VOLTS, MAX_AMPS*1000);
    // FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, 5);

    simpap_init(&simpap_ctx);

    delay(1000);

    // Read configuration from EEPROM if exist
    if(!state_load(&state_t)) {
        print("[Info] Setting default app state");
        // Initial state - Rainbow
        state_reset(&state_t);
        state_save(&state_t);
    }
}

void loop()
{
    if((stop - start) > CYCLE_MAX_DURATION) {
        print("[Error] Overrun");
    }
    start = millis();

    if(state_t.initialized) {
        state_update(&state_t);
        FastLED.show();
    }

    // Receive input
    while (Serial.available()) {
        uint8_t ch = Serial.read();
        simpap_accept_char(&simpap_ctx, ch);
    }

    delay(BASE_PERIOD);

    stop = millis();
}
