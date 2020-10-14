#pragma once

#include "leds.hpp"

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
