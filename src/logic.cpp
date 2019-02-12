#include <Arduino.h>

#include "logic.h"
#include "effects.h"

int _on(struct int_vars_t * vars){
    if(vars->last_cmd == on)
        return on;

    if(vars->last_cmd == off){
        return change;
    }

    return on;
}

int _change(struct int_vars_t * vars){
    if(vars->delay != 0){
        return wait;
    }

    vars->counter += 110;

    if(vars->last_cmd == on){
        if(vars->bright == 255){
            return on;
        } else{
            if (vars->mode == 1){
                vars->bright = effects_smooth(vars->counter, false);
                return change;
            } else{
                vars->bright = 255;
                vars->counter = 0;
                // Reset to default
                return on;
            }
        }
    }

    if(vars->last_cmd == off){
        if(vars->bright == 0){
            vars->counter = 0;
            return off;
        } else{
            if(vars->mode == 1){
                vars->bright = effects_smooth(vars->counter, true);
                return change;
            } else{
                vars->bright = 0;
                // Reset to default
                return off;
            }
        }
    }

    return change;
}

int _wait(struct int_vars_t * vars){
    if(vars->delay != 0){
        vars->delay--;
    } else{
        return change;
    }

    return wait;
}

int _off(struct int_vars_t * vars){
    if(vars->last_cmd == off)
        return off;

    if(vars->last_cmd == on){
        return change;
    }

    return off;
}

