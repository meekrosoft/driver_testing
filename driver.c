

#include "HardwareAbstraction.h"

#define DRIVER_OUTPUT_REGISTER 0xFFAA
#define DRIVER_INPUT_REGISTER  0XFFAB

void write_to_driver(uint8_t val)
{
    IO_MEM_WR8(DRIVER_OUTPUT_REGISTER, val);
}

uint8_t read_from_driver()
{
    return IO_MEM_RD8(DRIVER_INPUT_REGISTER);
}
