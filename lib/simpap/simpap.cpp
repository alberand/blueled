#include "simpap.hpp"

uint16_t crc16(uint8_t* data_p, uint8_t length)
{
    uint8_t x;
    uint16_t crc = 0xFFFF;

    while (length--) {
        x = crc >> 8 ^ *data_p++;
        x ^= x>>4;
        crc = (crc << 8) ^ ((uint16_t)(x << 12)) ^ \
              ((uint16_t)(x <<5)) ^ ((uint16_t)x);
    }
    return crc;
}

int8_t simpap_decode(struct simpap* p)
{
    if(!p->finished) {
        return -1;
    }

    if(p->index < 3) {
        return -2;
    }

    if(p->buffer[0] != '~' || p->buffer[p->index] != '~') {
        return -3;
    }

    // len - 1 byte for end flag - 2 bytes for crc
    uint8_t len = p->index - 3;
    uint16_t crc = crc16(p->buffer + 1, len);
    uint16_t crc_recv = (p->buffer[p->index - 2] << 8) | p->buffer[p->index - 1];

    if(crc != crc_recv) {
        return -4;
    }

    for(int i = 1; i < (p->index - 2); i++) {
        p->data[i - 1] = p->buffer[i];
    }

    return 0;
}

int8_t simpap_encode(struct simpap* p, uint8_t* msg, uint8_t len)
{
    if(len > MAX_SIZE || len == 0) {
        return -1;
    }

    p->buffer[0] = '~';
    for(int i = 1; i < len + 1; i++) {
        p->buffer[i] = (uint8_t)msg[i - 1];
    }
    uint16_t crc = crc16((uint8_t*)msg, len);
    p->buffer[len + 1] = (uint8_t)((crc >> 8) & 0xFF);
    p->buffer[len + 2] = (uint8_t)(crc & 0xFF);
    p->buffer[len + 3] = '~';

    return 0;
}

int8_t simpap_accept_char(struct simpap* p, uint8_t ch)
{
    if(p->index == BUFFER_SIZE) {
        simpap_init(p);

        return -1;
    }

    // simple state machine for parser
    if(ch == '~' && !p->started) {
        simpap_init(p);
        p->started = true;
        p->buffer[p->index++] = ch;

        return 0;
    }

    if(ch != '~' && p->started) {
        p->buffer[p->index++] = ch;

        return 0;
    }

    if(ch == '~' && p->started) {
        p->finished = true;
        p->started = false;
        p->buffer[p->index] = ch;

        int rc = 0;
        if((rc = simpap_decode(p)) == 0) {
            simpap_handler(p->data, p->index + 1 - SIMPAP_OVERHEAD);
            simpap_init(p);
        } else {
            return rc;
        }

        return 0;
    }

    return -2;
}

// Interface
void simpap_send(struct simpap* p, uint8_t* msg, uint8_t len)
{
    if(simpap_encode(p, msg, len) == 0) {
        for(int i = 0; i < (len + SIMPAP_OVERHEAD); i++) {
            simpap_send_char(p->buffer[i]);
        }
    }
}

int8_t simpap_accept(struct simpap* p, uint8_t* msg, uint8_t len)
{
    for(int i = 0; i < len; i++) {
        int rc = 0;
        if((rc = simpap_accept_char(p, (uint8_t)msg[i])) != 0) {
            return rc;
        }
    }

    return 0;
}

void simpap_init(struct simpap* simpap_ctx)
{
    simpap_ctx->index = 0;
    simpap_ctx->overrun = false;
    simpap_ctx->started = false;
    simpap_ctx->finished = false;
    for(int i = 0; i < BUFFER_SIZE; i++) {
        simpap_ctx->buffer[i] = 0;
    }
    for(int i = 0; i < MAX_SIZE; i++) {
        simpap_ctx->data[i] = 0;
    }
}
