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
    void (*leds_update)(CRGB*, uint16_t, const struct animation_config*);
    // Size of the received data in bytes
    uint8_t size;
    // Array for animation parameters
    uint32_t* params;
};

struct animation_state
{
    uint16_t iteration;
};

void animation_state_reset();
void animation_state_update(CRGB* leds, uint16_t num_leds,
                            const struct animation_config* config);

void fadeall(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void solid(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void gradient(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void rainbow(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void cylon(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void stroboscope(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void confetti(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void sinelon(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void bpm(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void juggle(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void fadeinout(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void twinkle(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void snowsparkle(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void train(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void color_wipe(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void rainbow_classic(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void theater_chase(CRGB* leds, uint16_t num_leds, const struct animation_config* config);
void fire(CRGB* leds, uint16_t num_leds, const struct animation_config* config);

static struct animation_config configs[] = {
    {
        .id = 0x41,
        .delay = 10,
        .leds_update = solid,
        .size = 3,
        .params = nullptr,
    },
    {
        .id = 0x42,
        .delay = 10,
        .leds_update = gradient,
        .size = 20,
        .params = nullptr,
    },
    {
        .id = 0x43,
        .delay = 20,
        .leds_update = cylon,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x44,
        .delay = 10,
        .leds_update = rainbow,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x45,
        .delay = 10,
        .leds_update = stroboscope,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x46,
        .delay = 10,
        .leds_update = confetti,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x47,
        .delay = 10,
        .leds_update = sinelon,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x48,
        .delay = 10,
        .leds_update = bpm,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x49,
        .delay = 10,
        .leds_update = juggle,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x4a,
        .delay = 10,
        .leds_update = fadeinout,
        .size = 1,
        .params = nullptr,
    },
    {
        .id = 0x4b,
        .delay = 10,
        .leds_update = twinkle,
        .size = 1,
        .params = nullptr,
    },
    {
        .id = 0x4c,
        .delay = 10,
        .leds_update = snowsparkle,
        .size = 2,
        .params = nullptr,
    },
    {
        .id = 0x4d,
        .delay = 50,
        .leds_update = train,
        .size = 1,
        .params = nullptr,
    },
    {
        .id = 0x4e,
        .delay = 10,
        .leds_update = color_wipe,
        .size = 1,
        .params = nullptr,
    },
    {
        .id = 0x4f,
        .delay = 20,
        .leds_update = rainbow_classic,
        .size = 0,
        .params = nullptr,
    },
    {
        .id = 0x50,
        .delay = 200,
        .leds_update = theater_chase,
        .size = 3,
        .params = nullptr,
    },
    {
        .id = 0x51,
        .delay = 20,
        .leds_update = fire,
        .size = 0,
        .params = nullptr,
    },
};
