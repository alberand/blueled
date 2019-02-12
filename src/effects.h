#ifndef __EFFECTS_H__
#define __EFFECTS_H__

#include <stdint.h>

#define PI M_PI

struct effects_attr_t{
    uint32_t position;
    uint32_t range;
    float cycle_half;
    uint8_t shift;
};

void effects_attr_init(struct effects_attr_t * attr);

/**
 * Basically 2**x growth in range from 0 to value_range.
 *
 */
float effects_breath(struct effects_attr_t * attr);

/**
 * Slow sinusoidal grow during 3 seconds. Return values from 0 to 255
 */
int effects_smooth(int t, bool down);

#endif // __EFFECTS_H__
