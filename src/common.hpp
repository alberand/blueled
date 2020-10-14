#pragma once

#include "simpap.hpp"

#define COUNT_OF(x) ((sizeof(x)/sizeof(0[x])) / ((size_t)(!(sizeof(x) % sizeof(0[x])))))

#define get_u8(d) ((uint8_t)(d[0]))
#define get_u16(d) ((uint16_t)(((uint16_t)d[0] << 8) + d[1]))
#define get_u32(d) ((uint32_t)(((uint32_t)d[0] << 24) + \
	((uint32_t)d[1] << 16) + \
	((uint32_t)d[2] << 8) + \
	d[3]))

/* Communication protocol context */
extern struct simpap simpap_ctx;

// Integrate simpap with printf
// TODO to be deleted
void print(const char *__fmt, ...);
