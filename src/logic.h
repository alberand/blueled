#ifndef __LOGIC_H__
#define __LOGIC_H__

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include "automata.h"
#include "effects.h"

#define N_STATES 4

// Internal variables
struct int_vars_t{
    uint32_t color;
    uint8_t bright;
    uint8_t delay;
    uint8_t last_cmd;
    uint8_t mode;
    uint32_t counter;
};

// Define states
enum States{
    on,
    off,
    change,
    wait
};

// States
int _on(struct int_vars_t * vars);
int _change(struct int_vars_t * vars);
int _wait(struct int_vars_t * vars);
int _off(struct int_vars_t * vars);

#endif // __LOGIC_H__
