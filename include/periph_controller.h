#ifndef __PERIPH_CONTROLLER_H
#define __PERIPH_CONTROLLER_H

#include <systemc.h>
#include <spi_master.h>

// Register map of bus slave
#define PERIPH_OUT_REG   0x00000000
#define PERIPH_IN_REG  0x00000004

#define PERIPH_STATE_REG  0x00000008
#define PERIPH_START  PERIPH_STATE_REG
#define PERIPH_READY  (PERIPH_STATE_REG+0x00000001)
#define PERIPH_BUSY  (PERIPH_STATE_REG+0x00000002)
#define PERIPH_ERROR  (PERIPH_STATE_REG+0x00000003)


SC_MODULE(periph_controller)
{
    sc_in<bool> hclk_i;
	sc_in<bool> hresetn_i;
    sc_in<sc_uint<32>>  haddr_bi;
    sc_in<sc_uint<32>>  hwdata_bi;
	sc_in<bool> hwrite_i;
	sc_in<bool> hsel_i;
    sc_out<sc_uint<32>> hrdata_bo;	
	
	sc_in<bool> miso_i;	
	sc_out<bool> mosi_o;    
	sc_out<bool> sck_o;
    sc_out<bool> ss1_o;
	sc_out<bool> ss2_o;
	sc_out<bool> ss3_o;
	
	sc_signal<bool> rst_sig;
	sc_signal<bool> start, ready, busy;
	sc_signal<sc_uint<2>> slave_b;
	sc_signal<sc_uint<8>> data_out_b;
	sc_signal<sc_uint<8>> data_in_b;
	
	spi_master *spi;
    
    SC_CTOR(periph_controller)
    {
		spi = new spi_master("spi_master");
			spi->clk_i(hclk_i);
			spi->rst_i(rst_sig);
			spi->start_i(start);
			spi->slave_i(slave_b);
			spi->data_in_bi(data_in_b);
			spi->busy_o(busy);
			spi->ready_o(ready);
			spi->data_out_bo(data_out_b);
			spi->miso_i(miso_i);
			spi->mosi_o(mosi_o);
			spi->sck_o(sck_o);
			spi->ss1_o(ss1_o);
			spi->ss2_o(ss2_o);
			spi->ss3_o(ss3_o);
		
		data_in_b.write(0);
		slave_b.write(0);
		
        SC_METHOD(bus_slave);
		sensitive << hclk_i.pos() << hresetn_i.pos();            
    }
    
    void set_base_address(sc_uint<32> base_addr)
    {
        this->base_addr = base_addr;
    }
    
private:
    sc_uint<32> base_addr;

    void bus_slave();
    
    sc_uint<32> execute_read(sc_uint<16> addr);
    void execute_write(sc_uint<16> addr, sc_uint<32> data);
};

#endif // __PERIPH_CONTROLLER_H