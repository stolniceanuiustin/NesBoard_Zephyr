#ifndef BUS_HEADERGUARD
#define BUS_HEADERGUARD
#include <stdint.h>

typedef uint8_t byte;


extern byte controller[2];
extern byte controller_state[2];

void bus_reset();

#endif