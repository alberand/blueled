#ifndef __COMMON_HPP__
#define __COMMON_HPP__

#include "simpap.hpp"

extern struct simpap simpap_ctx;

// Integrate simpap with printf
void print(const char *__fmt, ...);

#endif // __COMMON_HPP__
