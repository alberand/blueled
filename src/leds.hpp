#pragma once

#include <stdint.h>

#define FASTLED_ALLOW_INTERRUPTS 1
#include <FastLED.h>

#include "utils.hpp"

#define POSITION_IN_MIDDLE(i, p) (i == (uint16_t)int(p/2))
#define POSITION_IN_SECOND_HALF(i, p) (i >= (uint16_t)int(p/2))
#define POSITION_IN_FIRST_HALF(i, p) (i < (uint16_t)int(p/2))
#define POSITION_IN_FIRST_QUARTER(i, p) (i < (uint16_t)int(p/4))
#define POSITION_IN_SECOND_QUARTER(i, p) ((uint16_t)int(p/4) <= i < 2*(uint16_t)int(p/4))
#define POSITION_IN_THIRD_QUARTER(i, p) (2*(uint16_t)int(p/4) <= i < 3*(uint16_t)int(p/4))
#define POSITION_IN_FORTH_QUARTER(i, p) (3*(uint16_t)int(p/4) <= i < p)

struct animation_config
{
    uint8_t id;
    uint16_t delay;
    void (*payload_handler)(uint8_t*, uint8_t);
    void (*leds_update)(CRGB*, uint16_t);
};

struct animation_state
{
    // dynamics
    uint16_t iteration;
    // multi-color
    uint32_t colors[20];
    uint8_t index;
    uint8_t num;
};

void animation_state_reset(const struct animation_config* animation_config);
void animation_state_update(CRGB* leds, uint16_t num_leds,
                            const struct animation_config* animation_config);

void solid_handler(uint8_t* payload, uint8_t len);
void gradient_handler(uint8_t* payload, uint8_t len);

void fadeall(CRGB* leds, uint16_t num_leds);

void solid(CRGB* leds, uint16_t num_leds);
void gradient(CRGB* leds, uint16_t num_leds);
void rainbow(CRGB* leds, uint16_t num_leds);
void cylon(CRGB* leds, uint16_t num_leds);
void stroboscope(CRGB* leds, uint16_t num_leds);
void confetti(CRGB* leds, uint16_t num_leds);
void sinelon(CRGB* leds, uint16_t num_leds);
void bpm(CRGB* leds, uint16_t num_leds);
void juggle(CRGB* leds, uint16_t num_leds);
void fadeinout(CRGB* leds, uint16_t num_leds);
void twinkle(CRGB* leds, uint16_t num_leds);
void snowsparkle(CRGB* leds, uint16_t num_leds);
void train(CRGB* leds, uint16_t num_leds);
void color_wipe(CRGB* leds, uint16_t num_leds);
void rainbow_classic(CRGB* leds, uint16_t num_leds);
void theater_chase(CRGB* leds, uint16_t num_leds);
void fire(CRGB* leds, uint16_t num_leds);

static const struct animation_config configs[] = {
    {
        .id = 0x41,
        .delay = 10,
        .payload_handler = solid_handler,
        .leds_update = solid,
    },
    {
        .id = 0x42,
        .delay = 10,
        .payload_handler = gradient_handler,
        .leds_update = gradient,
    },
    {
        .id = 0x43,
        .delay = 20,
        .payload_handler = NULL,
        .leds_update = cylon,
    },
    {
        .id = 0x44,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = rainbow,
    },
    {
        .id = 0x45,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = stroboscope,
    },
    {
        .id = 0x46,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = confetti,
    },
    {
        .id = 0x47,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = sinelon,
    },
    {
        .id = 0x48,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = bpm,
    },
    {
        .id = 0x49,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = juggle,
    },
    {
        .id = 0x4a,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = fadeinout,
    },
    {
        .id = 0x4b,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = twinkle,
    },
    {
        .id = 0x4c,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = snowsparkle,
    },
    {
        .id = 0x4d,
        .delay = 50,
        .payload_handler = NULL,
        .leds_update = train,
    },
    {
        .id = 0x4e,
        .delay = 10,
        .payload_handler = NULL,
        .leds_update = color_wipe,
    },
    {
        .id = 0x4f,
        .delay = 20,
        .payload_handler = NULL,
        .leds_update = rainbow_classic,
    },
    {
        .id = 0x50,
        .delay = 200,
        .payload_handler = NULL,
        .leds_update = theater_chase,
    },
    {
        .id = 0x51,
        .delay = 20,
        .payload_handler = NULL,
        .leds_update = fire,
    },
};
