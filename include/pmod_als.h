#ifndef __PMOD_ALS_H
#define __PMOD_ALS_H

#include <systemc.h>
#include <spi_slave.h>

SC_MODULE(Pmod_ALS)
{
	sc_in<bool> sck_i;
	sc_in<bool> cs_i;
	sc_out<bool> sdo_o;
	
	sc_uint<8> sensor;
	
	sc_signal<bool> mosi_sig;
	sc_signal<sc_uint<8>> data_sig;
	
	spi_slave *spi;
    
    SC_CTOR(Pmod_ALS)
    {
        sdo_o.initialize(0);
		
		spi = new spi_slave("spi_slave");
			spi->sck_i(sck_i);
			spi->miso_o(sdo_o);
			spi->ss_i(cs_i);
			spi->mosi_i(mosi_sig);
			spi->data_bi(data_sig);
		
		mosi_sig.write(false);
        
        SC_THREAD(input_light);
        sensitive << sck_i.pos();
    }
    
private:
	void input_light();
};

#endif // __PMOD_ALS_H