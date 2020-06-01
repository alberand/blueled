#ifndef __LEDS_HPP__
#define __LEDS_HPP__

#include <stdint.h>

#include <FastLED.h>

#include "utils.hpp"

#define ZOOMING_BEATS_PER_MINUTE 122

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

#endif // __LEDS_HPP__
