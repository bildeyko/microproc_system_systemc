#ifndef __SPI_MASTER_H
#define __SPI_MASTER_H

#include <systemc.h>

SC_MODULE(spi_master)
{
    // External interface
    
    sc_in<bool> clk_i;
    sc_in<bool> rst_i;
	sc_in<bool> start_i;
	sc_in<sc_uint<2>> slave_i;
	sc_in<sc_uint<8>> data_in_bi;
	sc_out<bool> busy_o;
	sc_out<bool> ready_o;
	sc_out<sc_uint<8>> data_out_bo;
	
	// Input from slave
	sc_in<bool> miso_i;    
	
	// Output to slave
    sc_out<bool> mosi_o;
	sc_out<bool> sck_o;
	sc_out<bool> ss1_o;
    sc_out<bool> ss2_o;
    sc_out<bool> ss3_o;
    
    // Internal variables
    
	unsigned int state = 0;
	sc_uint<2> clk_count = 0;
	sc_uint<3> bit_count = 0;
	sc_uint<8> data_reg = 0;
    
    // Constructor
    
    SC_CTOR(spi_master)
    {
        // Sequential block
        SC_METHOD(transmission_block);
        sensitive << clk_i.pos() << rst_i;
        
        // Combinational block
        SC_METHOD(demux_block);
        sensitive << slave_i;
    }
    
    // Methods
    
    void transmission_block();
	void demux_block();
};

#endif // __SPI_MASTER_H
