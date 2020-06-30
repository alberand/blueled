#include <stdio.h>
#include <stdarg.h>

#include <Arduino.h>
#include <SoftwareSerial.h>

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

// Define the array of leds
CRGB* leds;
static bool initialized = false;

uint16_t NUM_LEDS;

struct simpap simpap_ctx;
static uint16_t start, stop;

struct state
{
    uint16_t iteration;
    uint16_t num_leds;
    uint8_t animation;
    const struct animation_config* config;
} state_t;

void print(const char *__fmt, ...)
{
    char buf[50] = { 0 };
    va_list va;
    va_start(va, __fmt);
    vsprintf(buf, __fmt, va);
    va_end(va);

    simpap_send(&simpap_ctx, (uint8_t*)buf, sizeof(buf));
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
        initialized = true;
        print("[Info] Initialization complete");
    } else if(!initialized) {
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
            animation_state_reset(state_t.config);
            if(configs[i].payload_handler != NULL) {
                configs[i].payload_handler(&(data[PAYLOAD_OFFSET]),
                                           len - PAYLOAD_OFFSET);
            }
        }
    }
}

void state_update()
{
    state_t.iteration++;

    if(state_t.iteration%(state_t.config->delay/BASE_PERIOD) == 0) {
        animation_state_update(leds, state_t.num_leds, state_t.config);
    }

    FastLED.show();
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

    // Initial state - Rainbow
    state_t.iteration = 0;
    state_t.num_leds = 0;
    state_t.animation = 0x4e;
    state_t.config = &configs[3];
}

void loop()
{
    if((stop - start) > CYCLE_MAX_DURATION) {
        print("[Error] Overrun");
    }
    start = millis();

    if(initialized) {
        state_update();
    }

    // Receive input
    while (Serial.available()) {
        uint8_t ch = Serial.read();
        simpap_accept_char(&simpap_ctx, ch);
    }

    delay(BASE_PERIOD);

    stop = millis();
}
