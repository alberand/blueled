#include <math.h>

#include "effects.h"

void effects_attr_init(struct effects_attr_t * attr){
    attr->position = 0;
    attr->range = 256;
    attr->cycle_half = 3000.0;
    attr->shift = 5;
}

float effects_breath(struct effects_attr_t * attr){
    if (attr->position == attr->range)
        attr->position = 0;

    // 6 seconds sin 3000*2
    return (exp(sin(attr->position++/attr->cycle_half*PI)) - 0.36787944)*108.0 + attr->shift;
}

int effects_smooth(int t, bool down){
    /**
     * 3000 defines the period when sin() will come to zero (solution)
     * 3000 means that sin() half cycle is 3000 milliseconds
     * 
     * 5 is lower limit. We don't want to got to zero
     *
     * @int t time step from 0 to `half_cycle`
     * @int down if true 255 -> 0 instead of 0 -> 255
     *
     * @return int in 0 - 255 range
     */

    // In milliseconds
    float half_cycle = 3000.0;
    uint16_t upper_limit = 255;
    int sign = 1;

    if (t > half_cycle || t < 0)
        return -1;

    if(down == true)
        sign = -1;

    int b = (int)((exp(sin(t/half_cycle*PI + sign*half_cycle/2.0)) - 0.36787944)*108.0);

    if (b > upper_limit)
        b = upper_limit;

    return b;
}
