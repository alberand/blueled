#pragma once

#include <stdint.h>

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
                            struct animation_config* animation_config);

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
