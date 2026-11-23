#include "bus.h"

void bus_reset()
{
    controller[0] = 0x00;
    controller[1] = 0x00;
    controller_state[0] = 0x00;
    controller_state[1] = 0x00;
}
