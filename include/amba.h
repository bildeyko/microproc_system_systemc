#ifndef __AMBA_H
#define __AMBA_H

#include <systemc.h>

SC_MODULE(amba)
{
	// input from Master
	sc_in<sc_uint<32>>  haddr_bi;	
	
	// input from Slaves
	sc_in<sc_uint<32>> hrdata_1_bi;
	sc_in<sc_uint<32>> hrdata_2_bi;
	
	// output to Master
	sc_out<sc_uint<32>> hrdata_bo;
	
	// output to Slaves
	sc_out<bool> hsel_s1_o;	
	sc_out<bool> hsel_s2_o;	
	
	SC_CTOR(amba)
    {
		SC_METHOD(decoder_block);
        sensitive << haddr_bi;
		
		SC_METHOD(mux_block);
        sensitive << hrdata_1_bi << hrdata_2_bi << mul_sel;
	}
	
private:
	sc_signal<sc_uint<16>> mul_sel; 
	
	void decoder_block();
	void mux_block();
};

#endif // __AMBA_H