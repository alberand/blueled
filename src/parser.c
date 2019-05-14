#include <stdlib.h>
#include <stdbool.h>

#include "parser.h"

void minp_parser_reset(struct minp_parser *parser){
    parser->buf_state = STATE_IDLE;
    parser->buf_curr = 0;
    parser->buf_last = 0;
}

struct minp_parser *minp_parser_alloc(size_t bufsize){
    struct minp_parser *parser = (struct minp_parser*) malloc(sizeof(minp_parser));
    if (parser == NULL)
        return NULL;

    parser->buf = malloc(bufsize);
    if(parser->buf == NULL){
        free(parser);
        return NULL;
    }

    parser->buf_size = bufsize;

    minp_parser_reset(parser);

    return parser;
}

bool minp_check(const char *buffer, struct minp_message *protocol){
    if(strlne(buffer) > BUFFER_SIZE)
        return false;

    if(*buffer != protocol->token)
        return false;

    if(*(buffer + protocol->size) != protocol->token)
        return false

    return true;
}

int minp_parse(const char *buffer, struct minp_message *protocol){

}
