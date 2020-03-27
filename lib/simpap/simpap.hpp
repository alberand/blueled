#ifndef __SIMPAP_HPP__
#define __SIMPAP_HPP__

// Won't for for duplex

#include <stdint.h>

#define MAX_SIZE 20
#define SIMPAP_OVERHEAD 4
#define BUFFER_SIZE (MAX_SIZE + SIMPAP_OVERHEAD)

struct simpap {
	uint8_t buffer[BUFFER_SIZE];
    uint8_t index;
    bool overrun;

    // Parser status
    bool started;
    bool finished;

    // output
	uint8_t data[MAX_SIZE];
};

uint16_t crc16(uint8_t* data_p, uint8_t length);

int8_t simpap_encode(struct simpap* simpap_ctx, uint8_t* msg, uint8_t len);
int8_t simpap_decode(struct simpap* simpap_ctx);

int8_t simpap_accept_char(struct simpap* simpap_ctx, uint8_t ch);

// Defined by user
extern void simpap_send_char(uint8_t ch);
extern void simpap_handler(uint8_t* data, uint8_t len);

// Interface
void simpap_init(struct simpap* simpap_ctx);
void simpap_send(struct simpap* simpap_ctx, uint8_t* msg, uint8_t len);
// 0 just fine
// -1 overflow
// -2 message doesn't started yet
// -3 failed to decode (bad crc)
int8_t simpap_accept(struct simpap* simpap_ctx, uint8_t* msg, uint8_t len);

#endif // __SIMPAP_HPP__
