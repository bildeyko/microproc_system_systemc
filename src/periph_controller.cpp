#include <systemc.h>

#include <periph_controller.h>

#include <stdio.h>

void periph_controller::bus_slave()
{
    static bool wr_flag = false;
    static sc_uint<32> wr_addr = 0;
    
	rst_sig.write(!hresetn_i.read());
	if (!hresetn_i.read())
    {
		data_in_b.write(0);
		printf("**periph_controller - bus_slave** periph_controller is reseted!\n");
    }
    else	if (hclk_i.read() && hsel_i.read())
    {
		if(ready.read())
		{
			slave_b.write(0);
			printf("**periph_controller - bus_slave** SPI transfer ready\n");
		}
		
		if(start)
		{
			start.write(0);
		}
		
       if (wr_flag)
        {
            execute_write((sc_uint<16>) (wr_addr - base_addr), hwdata_bi.read());
            wr_flag = false;
        }
        
        if (hwrite_i.read() && !busy)
        {
            wr_flag = true;
            wr_addr = haddr_bi.read();
        }
        else
        {
            hrdata_bo.write((sc_uint<8>) (execute_read(haddr_bi.read() - base_addr)));
        }
    }
}

sc_uint<32> periph_controller::execute_read(sc_uint<16> addr)
{
    sc_uint<32> data;

    switch (addr)
    {
    case PERIPH_OUT_REG:
        data = data_out_b;
        break;
    case PERIPH_START:
        data = start;
        break;
	case PERIPH_READY:
        data = ready;		
        break;
	case PERIPH_BUSY:
        data = busy;
        break;
    default:
        data = 0;
        break;
    }
    
    return data;
}

void periph_controller::execute_write(sc_uint<16> addr, sc_uint<32> data)
{
    switch (addr)
    {
    case PERIPH_START:
        start = data;
		slave_b.write(1);		
		printf("**periph_controller - execute_write** SPI transfer started!\n");
        break;
    default:
        break;
    }
}