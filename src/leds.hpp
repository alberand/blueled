#ifndef __LEDS_HPP__
#define __LEDS_HPP__

#include <stdint.h>

#include <FastLED.h>

#include "utils.hpp"

#define ZOOMING_BEATS_PER_MINUTE 122

#define POSITION_IN_MIDDLE(i, p) (i == int(p/2))
#define POSITION_IN_SECOND_HALF(i, p) (i > int(p/2))
#define POSITION_IN_FIRST_HALF(i, p) (i < int(p/2))
#define POSITION_IN_FIRST_QUARTER(i, p) (i < int(p/4))
#define POSITION_IN_SECOND_QUARTER(i, p) (int(p/4) < i < 2*int(p/4))
#define POSITION_IN_THIRD_QUARTER(i, p) (2*int(p/4) < i < 3*int(p/4))
#define POSITION_IN_FORTH_QUARTER(i, p) (3*int(p/4) < i < p)

extern uint16_t NUM_LEDS;

void solid_handler(uint8_t* payload, uint8_t len);
void gradient_handler(uint8_t* payload, uint8_t len);

void fadeall(CRGB* leds);

void solid(CRGB* leds);
void gradient(CRGB* leds);
void rainbow(CRGB* leds);
void cylon(CRGB* leds);
void stroboscope(CRGB* leds);
void confetti(CRGB* leds);
void sinelon(CRGB* leds);
void bpm(CRGB* leds);
void juggle(CRGB* leds);
void fadeinout(CRGB* leds);
void twinkle(CRGB* leds);
void snowsparkle(CRGB* leds);
void train(CRGB* leds);
void color_wipe(CRGB* leds);

#endif // __LEDS_HPP__
