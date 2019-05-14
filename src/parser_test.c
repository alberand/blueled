#include "wvtest.h"

#include <stdint.h>

#include "parser.h"

struct minp_message {
    uint32_t id;
    char message[100];
    float sensor;
    char status[50];
};


int main(int argc, int **argv){
    char b[10] = "~123;Hello world;3.1415;er.rror~";

    struct minp_message msg;
    struct minp_parser parser;

    minp_parser_init('~', ';', &msg);

    minp_parser_parse(b, &msg, &parser);

    printf("id: %d\n", msg.id);
    printf("message: %s\n", msg.message);
    printf("id: %f\n", msg.sensor);
    printf("id: %s\n", msg.status);



    /*struct minp_protocol proto = {
        token = '~',    
        delimeter = ';',
        size = 10,
        message = *message;
    };*/

    return 0;
}
