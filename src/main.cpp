#include <Arduino.h>

#include <fifo.h>

#define MAX_MSG_SIZE 124

void setup() {
    // initialize digital pin LED_BUILTIN as an output.
    pinMode(LED_BUILTIN, OUTPUT);
    FIFO<uint8_t>* tx_fifo = new FIFO<uint8_t>(10);

    tx_fifo->getsize();
}

// the loop function runs over and over again forever
void loop() {
    digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
    delay(1000);                       // wait for a second
    digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
    delay(1000);                       // wait for a second
}
