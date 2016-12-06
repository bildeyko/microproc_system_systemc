#include <all_system.h>
#include <cpu_sw_bus.h>
#include <cpu_sw_dindout.h>

void dout_write(unsigned long data)
{
    bus_write(DIN_DOUT_BASE + DIN_DOUT_OUT_REG, data);
}

unsigned long din_read()
{
    return bus_read(DIN_DOUT_BASE + DIN_DOUT_IN_REG);
}