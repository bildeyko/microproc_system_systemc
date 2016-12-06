#include <all_system.h>
#include <cpu_sw_bus.h>
#include <cpu_sw_periph.h>

void periph_set_start(unsigned long data)
{
	periph_write(PERIPH_START, data);
}

unsigned long periph_get_ready()
{
	return periph_read(PERIPH_READY);
}

unsigned long periph_get_data()
{
	return periph_read(PERIPH_OUT_REG);
}

void periph_write(unsigned long addr, unsigned long data)
{
    bus_write(PERIPHERAL_BASE + addr, data);
}

unsigned long periph_read(unsigned long addr)
{
    return bus_read(PERIPHERAL_BASE + addr);
}