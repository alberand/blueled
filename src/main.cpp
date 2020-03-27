#include <Arduino.h>
#include <SoftwareSerial.h>

#include "simpap.hpp"
#include "leds.hpp"
#include "utils.hpp"

// Software-Hardoware configuration
// Always 5V
#define MAX_VOLTS 5
#define MAX_AMPS 5
// Therefore, 25 W in total

// Application related
#define DATA_PIN PD7
#define CYCLE_MAX_DURATION 100

// Communication
#define PAYLOAD_OFFSET 2
#define STATE_SOLID 0x41
#define STATE_GRADIENT 0x42
#define STATE_GRADIENT_START 0x42
#define STATE_GRADIENT_COLOR 0x42
#define STATE_GRADIENT_FINISH 0x2142
#define STATE_CYLON 0x43
#define STATE_RAINBOW 0x44

// Define the array of leds
CRGB leds[NUM_LEDS];

struct simpap simpap_ctx;
static uint16_t start, stop;

struct state{
	uint8_t state;
	uint16_t delay;
} state_t;

// SoftwareSerial toSlave(10, 11);
void simpap_send_char(uint8_t ch){
    Serial.write(ch);
}

void simpap_handler(uint8_t* data, uint8_t len){
    digitalWrite(LED_BUILTIN, HIGH);

	uint16_t cmd = get_u16(data);

	switch(cmd){
		case STATE_SOLID:
			state_t.state = STATE_SOLID;
			solid_handler(&(data[PAYLOAD_OFFSET]), len - PAYLOAD_OFFSET);
		break;
		case STATE_GRADIENT:
			state_t.state = STATE_GRADIENT;
			gradient_handler(&(data[PAYLOAD_OFFSET]), len - PAYLOAD_OFFSET);
		break;
		case STATE_RAINBOW:
			state_t.state = STATE_RAINBOW;
		break;
		case STATE_CYLON:
			state_t.state = STATE_CYLON;
		break;
		default:
    		Serial.print("Don't know this command");
		break;
	}
}

void setup() {
    Serial.begin(115200);

    pinMode(LED_BUILTIN, OUTPUT);
    digitalWrite(LED_BUILTIN, LOW);

    set_max_power_in_volts_and_milliamps(MAX_VOLTS, MAX_AMPS*1000);
    FastLED.addLeds<WS2812B, DATA_PIN, RGB>(leds, NUM_LEDS);

    simpap_init(&simpap_ctx);

	state_t.state = STATE_RAINBOW;
	state_t.delay = 25;
}

void process(){
	// cylon
	switch(state_t.state){
		case STATE_SOLID:
			solid(leds);
		break;
		case STATE_GRADIENT:
			gradient(leds);
		break;
		case STATE_CYLON:
			cylon(leds);
		break;
		case STATE_RAINBOW:
			pride(leds);
		break;
	}

    FastLED.show();
	delay(state_t.delay);
}

void loop() {
	if((stop - start) > CYCLE_MAX_DURATION){
		simpap_send(&simpap_ctx, (uint8_t*)"[Error] Overrun", 15);
	}
	start = millis();

	process();

	// Receive input
    while (Serial.available()) {
        uint8_t ch = Serial.read();
        simpap_accept_char(&simpap_ctx, ch);
    }
	stop = millis();
}
