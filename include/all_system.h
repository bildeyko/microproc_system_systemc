#ifndef __ALL_SYSTEM_H
#define __ALL_SYSTEM_H

#include <systemc.h>

#include <cpu.h>
#include <amba.h>
#include <din_dout.h>
#include <periph_controller.h>
#include <pmod_als.h>

#define PERIPHERAL_BASE     0x10000000
#define DIN_DOUT_BASE     0x20000000

SC_MODULE(AllSystem)
{
    sc_clock *clk;
    sc_signal<bool> rst_n;
    sc_signal<sc_uint<32>> haddr;
    sc_signal<sc_uint<32>> hwdata;
    sc_signal<sc_uint<32>> hrdata;
	sc_signal<sc_uint<32>> hrdata_1;
	sc_signal<sc_uint<32>> hrdata_2;
    sc_signal<bool> hwrite;
    sc_signal<bool> hsel_s1;
	sc_signal<bool> hsel_s2;
    
    CPU *cpu;
	amba *amba_bus;
    DinDout *din_dout;
	periph_controller *periph;
	Pmod_ALS *als;
	
	sc_signal<bool> mosi, miso;
	sc_signal<bool> ss1, ss2, ss3;
	sc_signal<bool> sck;
    
    SC_CTOR(AllSystem)
    {
        clk = new sc_clock("clk", 10, SC_NS);
              
		hrdata_1.write(0);
        
		cpu = new CPU("CPU");
			cpu->hclk_i(*clk);
			cpu->haddr_bo(haddr);
			cpu->hwdata_bo(hwdata);
			cpu->hrdata_bi(hrdata);
			cpu->hwrite_o(hwrite);
		
		amba_bus = new amba("amba");
			amba_bus->haddr_bi(haddr);	
			amba_bus->hrdata_1_bi(hrdata_1);
			amba_bus->hrdata_2_bi(hrdata_2);
			amba_bus->hrdata_bo(hrdata);
			amba_bus->hsel_s1_o(hsel_s1);
			amba_bus->hsel_s2_o(hsel_s2);
		
        din_dout = new DinDout("DinDout");
			din_dout->set_base_address(DIN_DOUT_BASE);
			din_dout->hclk_i(*clk);
			din_dout->hresetn_i(rst_n);
			din_dout->haddr_bi(haddr);
			din_dout->hwdata_bi(hwdata);
			din_dout->hrdata_bo(hrdata_2);
			din_dout->hwrite_i(hwrite);
			din_dout->hsel_i(hsel_s2);
			
		periph = new periph_controller("periph_controller");
			periph->set_base_address(PERIPHERAL_BASE);
			periph->hclk_i(*clk);
			periph->hresetn_i(rst_n);
			periph->haddr_bi(haddr);
			periph->hwdata_bi(hwdata);
			periph->hrdata_bo(hrdata_1);
			periph->hwrite_i(hwrite);
			periph->hsel_i(hsel_s1);
			periph->miso_i(miso);	
			periph->mosi_o(mosi);    
			periph->sck_o(sck);
			periph->ss1_o(ss1);
			periph->ss2_o(ss2);
			periph->ss3_o(ss3);
			
		als = new Pmod_ALS("Pmod_ALS");
			als->sck_i(sck);
			als->cs_i(ss1);
			als->sdo_o(miso);
		
        SC_THREAD(stimuli);
        sensitive << *clk << rst_n;
    }
    
    ~AllSystem()
    {
        delete clk;
        
        delete cpu;
        delete din_dout;
    }
    
private:
    void stimuli();
};

#endif // __ALL_SYSTEM_H
