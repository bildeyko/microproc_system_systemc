#ifndef __CPU_SW_PERIPH_H
#define __CPU_SW_PERIPH_H

void periph_write(unsigned long addr, unsigned long data);
unsigned long periph_read(unsigned long addr);

void periph_set_start(unsigned long data);
unsigned long periph_get_ready();
unsigned long periph_get_data();

#endif // __CPU_SW_PERIPH_H
