#include <systemc.h>

#include <main.h>

AllSystem *ts;

int sc_main(int argc, char* argv[])
{
    sc_trace_file *f_trace;
    
    ts = new AllSystem("AllSystem");
    
    f_trace = sc_create_vcd_trace_file("waveforms");
    f_trace->set_time_unit(1, SC_PS);
    
    sc_trace(f_trace, *(ts->clk),    "clk");
    sc_trace(f_trace, ts->rst_n,  "rst_n");
    sc_trace(f_trace, ts->haddr,  "haddr");
    sc_trace(f_trace, ts->hwdata, "hwdata");
    sc_trace(f_trace, ts->hrdata, "hrdata");
	sc_trace(f_trace, ts->hrdata_1, "hrdata_1");
	sc_trace(f_trace, ts->hrdata_2, "hrdata_2");
    sc_trace(f_trace, ts->hsel_s1, "hsel_s1");
	sc_trace(f_trace, ts->hsel_s2, "hsel_s2");
	
	sc_trace(f_trace, ts->din_dout->leds, "leds");
	
	sc_trace(f_trace, ts->periph->start, "spi_start");
	sc_trace(f_trace, ts->periph->ready, "spi_ready");
	sc_trace(f_trace, ts->periph->busy, "spi_busy");
	sc_trace(f_trace, ts->sck, "spi_sck");
	sc_trace(f_trace, ts->mosi, "spi_mosi");
	sc_trace(f_trace, ts->miso, "spi_miso");
	sc_trace(f_trace, ts->ss1, "spi_ss1");
	sc_trace(f_trace, ts->ss2, "spi_ss2");
	sc_trace(f_trace, ts->ss3, "spi_ss3");
	
	sc_trace(f_trace, ts->als->sensor, "sensor");
	/*sc_trace(f_trace, ts->als->spi->data_reg, "slave_data_reg");
	sc_trace(f_trace, ts->als->spi->data_bi, "slave_data_bi");
	sc_trace(f_trace, ts->als->spi->ss_i, "slave_ss_i");
	sc_trace(f_trace, ts->als->spi->sck_i, "slave_sck_i");
	sc_trace(f_trace, ts->als->spi->mosi_i, "slave_mosi_i");
	sc_trace(f_trace, ts->als->spi->miso_o, "slave_miso_o");*/

    sc_start(2000, SC_NS);
    sc_stop();

    sc_close_vcd_trace_file(f_trace);
    
    delete ts;
    
    return 0;
}
