#include <Arduino.h>
#include <SoftwareSerial.h>

#include "simpap.hpp"
#include "leds.hpp"
#include "utils.hpp"

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

// Define the array of leds
CRGB* leds;
static bool initialized = false;

uint16_t NUM_LEDS;

struct simpap simpap_ctx;
static uint16_t start, stop;

struct state
{
    uint8_t state;
    uint16_t delay;
} state_t;

struct state_config
{
    uint8_t id;
    void (*payload_handler)(uint8_t*, uint8_t);
    void (*state_update)(CRGB*);
};

static const struct state_config configs[] = {
    {.id = 0x41, .payload_handler = solid_handler,      .state_update = solid},
    {.id = 0x42, .payload_handler = gradient_handler,   .state_update = gradient},
    {.id = 0x43, .payload_handler = NULL,               .state_update = cylon},
    {.id = 0x44, .payload_handler = NULL,               .state_update = rainbow},
    {.id = 0x45, .payload_handler = NULL,               .state_update = stroboscope},
    {.id = 0x46, .payload_handler = NULL,               .state_update = confetti},
    {.id = 0x47, .payload_handler = NULL,               .state_update = sinelon},
    {.id = 0x48, .payload_handler = NULL,               .state_update = bpm},
    {.id = 0x49, .payload_handler = NULL,               .state_update = juggle},
    {.id = 0x4a, .payload_handler = NULL,               .state_update = fadeinout},
    {.id = 0x4b, .payload_handler = NULL,               .state_update = twinkle},
    {.id = 0x4c, .payload_handler = NULL,               .state_update = snowsparkle},
    {.id = 0x4d, .payload_handler = NULL,               .state_update = train},
    {.id = 0x4e, .payload_handler = NULL,               .state_update = color_wipe},
};

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
        initialized = true;
        simpap_send(&simpap_ctx, (uint8_t*)"[Info] Initialization complete", 30);
    } else if(!initialized) {
        simpap_send(&simpap_ctx, (uint8_t*)"[Error] Not known number of LEDs", 32);
    } else {
        /* Apply animation */
        for(int i = 0; i < COUNT_OF(configs); i++) {
            if(configs[i].id != cmd) {
                continue;
            }

            simpap_send(&simpap_ctx, (uint8_t*)"[Info] Changing animation", 25);
            state_t.state = configs[i].id;
            if(configs[i].payload_handler != NULL) {
                configs[i].payload_handler(&(data[PAYLOAD_OFFSET]),
                                           len - PAYLOAD_OFFSET);
            }
        }
    }
}

void state_update()
{
    for(int i = 0; i < COUNT_OF(configs); i++) {
        if(configs[i].id != state_t.state) {
            continue;
        }

        configs[i].state_update(leds);
    }

    FastLED.show();
    delay(state_t.delay);
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
    state_t.state = 0x4e;
    state_t.delay = 25;
}

void loop()
{
    if((stop - start) > CYCLE_MAX_DURATION) {
        simpap_send(&simpap_ctx, (uint8_t*)"[Error] Overrun", 15);
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
    stop = millis();
}
