#ifndef __SPI_SLAVE_H
#define __SPI_SLAVE_H

#include <systemc.h>

SC_MODULE(spi_slave)
{
	// Output to master
	sc_out<bool> miso_o;    
	
	// Input from master
    sc_in<bool> mosi_i;
	sc_in<bool> sck_i;
	sc_in<bool> ss_i;
	
	// Input from device
	sc_in<sc_uint<8>> data_bi;
    
    // Internal variables
	sc_uint<8> data_reg = 0;
    
    // Constructor
    
    SC_CTOR(spi_slave)
    {
        // Sequential block
		SC_METHOD(data_block);
        sensitive << ss_i.neg();
		
        SC_METHOD(transmission_block);
        sensitive << sck_i.pos();
    }
    
    // Methods
    
    void transmission_block();
	void data_block();
};

#endif // __SPI_SLAVE_H
