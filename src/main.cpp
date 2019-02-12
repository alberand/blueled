#include <Arduino.h>

#include <FastLED.h>
#include <limits.h>

#include "automata.h"
#include "logic.h"

#define NUM_LEDS 5 // 27
#define DATA_PIN 3

#define TIMESTEP 10
#define STEP 5
#define MAX_BRIGHT 230
#define MIN_BRIGHT 20

// Define the array of leds
CRGB leds[NUM_LEDS];

static struct int_vars_t vars;
static int (*states[4])(struct int_vars_t * vars);

enum cmds{
  ON = (int)'n',
  OFF = (int)'f',
  SETBRIGHTNESS = (int)'b',
  SETCOLOR = (int)'c',
  SETMODE = (int)'m',
  WAIT = (int)'w'
};

void inline setColor(int i, CRGB color){
  leds[i] = color;
}

void setColors(CRGB color, uint16_t bright){
  for( int i = 0; i < NUM_LEDS; i++) {
    setColor(i, color);
  }
  FastLED.setBrightness(bright);
}

void setup() { 
    // Bluetooth module on UART
    Serial.begin(9600);
    Serial.setTimeout(100);
    FastLED.addLeds<WS2812B, DATA_PIN, GRB>(leds, NUM_LEDS);
    setColors(CRGB::Green, 100);
    FastLED.show();
    FastLED.setBrightness(0);

    STATE_INIT(on);
    STATE_INIT(off);
    STATE_INIT(change);
    STATE_INIT(wait);


    vars = {
        .color = CRGB::Green,
        .bright = 255,
        .delay = 0,
        .last_cmd = 0,
        .mode = 0,
        .counter = 0,
    };
}

int parse_cmd(char *cmd, uint8_t *cmd_c, long *param){
  *cmd_c = (uint8_t)cmd[0];
  cmd[0] = '0';
  *param = (uint32_t)strtoul(cmd, NULL, 10);
  if(param == ULONG_MAX){
    return -1;
  }else{
    return 0;
  }
}

int process_cmd(uint8_t cmd_c, uint32_t param){
  switch(cmd_c){
    case ON:
      vars.last_cmd = 0;
    break;
    case OFF:
        Serial.println("Set last cmd to 1");
      vars.last_cmd = 1;
    break;
    case SETBRIGHTNESS:
      vars.bright = param;
    break;
    case SETCOLOR:
      vars.color = param;
    break;
    case SETMODE:
      vars.mode = param;
    break;
    case WAIT:
      vars.delay = param*1000;
    break;
    default:
      return -1;
  }

  return 0;
}

void input_handler(void){
  if(Serial.available() > 0){
    char cmd[12] = { 0 };
    if(Serial.readBytes(cmd, 11) != 0){
      uint8_t cmd_c = (uint8_t)'f';
      uint32_t param = 0;
      if(parse_cmd(cmd, &cmd_c, &param) != -1){
        if(process_cmd(cmd_c, param) != -1){
          // update_state();
          ;
        }
      }
      Serial.flush();
      param = 0;
      cmd_c = (uint8_t)'f';
    }
  }
}


void loop() { 
    input_handler();

    // logic_step();
    AUTOMATA_STEP(vars);

    Serial.print("State: ");
    Serial.print(current);
    Serial.print("; color: ");
    Serial.print(vars.color);
    Serial.print("; bright: ");
    Serial.print(vars.bright);
    Serial.print("; delay: ");
    Serial.print(vars.delay);
    Serial.print("; last_cmd: ");
    Serial.print(vars.last_cmd);
    Serial.print("; mode: ");
    Serial.print(vars.mode);
    Serial.print("; counter: ");
    Serial.print(vars.counter);
    Serial.print("\r\n");

    setColors(vars.color, vars.bright);
    FastLED.show();


    delay(TIMESTEP);
}
