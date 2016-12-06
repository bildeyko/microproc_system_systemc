#include <systemc.h>

#include <amba.h>

void amba::decoder_block()
{
	static sc_uint<16> slave_addr = 0;
	
	slave_addr = haddr_bi.read().range(31,16);
	
	switch(slave_addr)
	{
		case 0x1000:
			hsel_s1_o.write(1);
			hsel_s2_o.write(0);
			mul_sel = slave_addr;
			break;
		case 0x2000:
			hsel_s1_o.write(0);
			hsel_s2_o.write(1);
			mul_sel = slave_addr;
			break;
		default:
			break;
	}
}

void amba::mux_block()
{
	switch(mul_sel.read())
	{
		case 0x1000:
			hrdata_bo.write(hrdata_1_bi);
			break;
		case 0x2000:
			hrdata_bo.write(hrdata_2_bi);
			break;
		default:
			break;
	}
}