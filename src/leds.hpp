#ifndef __LEDS_HPP__
#define __LEDS_HPP__

#include <stdint.h>

#include <FastLED.h>

#include "utils.hpp"

#define NUM_LEDS 27

static struct solid_params {
    uint32_t color;
} solid_params_t;

static struct gradient_params {
    uint32_t colors[20];
    uint8_t index;
    uint8_t num;
} gradient_params_t;


void solid_handler(uint8_t* payload, uint8_t len);
void gradient_handler(uint8_t* payload, uint8_t len);

void fadeall(CRGB* leds);
void solid(CRGB* leds);
void gradient(CRGB* leds);
void pride(CRGB* leds);
void cylon(CRGB* leds);

#endif // __LEDS_HPP__
