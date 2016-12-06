#include <systemc.h>

#include <spi_slave.h>

void spi_slave::data_block()
{	
	data_reg = data_bi.read();
}

void spi_slave::transmission_block()
{	
    if (!ss_i.read())
    {		
		miso_o.write(data_reg[7]);
		data_reg = data_reg << 1;				
    }
}