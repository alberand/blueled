#ifndef __MINP_H__
#define __MINP_H__

#ifdef __cplusplus
extern "C" {
#endif

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#define BUFFER_SIZE 51

enum minp_parser_state{
    STATE_IDLE,
    STATE_READ,
}

struct minp_protocol {
    uint8_t token;
    uint8_t delimeter;
    uint8_t size;
};

struct minp_parser{
    enum minp_parser_state state;
    struct minp_protocol *protocol;

    char *buf;
    size_t buf_size;
    size_t buf_curr;
    size_t buf_last;
}


void minp_parser_reset(struct minp_parser *parser);
struct minp_parser *minp_parser_alloc(size_t bufsize);
bool minp_check(const char *buffer, struct minp_message *protocol);
int minp_parse(const char *buffer, struct minp_message *protocol);

#ifdef __cplusplus
}
#endif

#endif //__MINP_H__
