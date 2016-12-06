#include <systemc.h>

#include <spi_master.h>

#include <stdio.h>

void spi_master::transmission_block()
{	
    if (rst_i.read())
    {
		state = 0;
		data_reg = 0;
		clk_count = 0;
		bit_count = 0;
		
		ready_o.write(false);
		busy_o.write(false);
		sck_o.write(false);
		mosi_o.write(false);
		data_out_bo.write(0);
    }
    else
    {
		ready_o.write(false);
		
		switch(state)
		{
			case 0:
				clk_count = 0;
				bit_count = 0;
				if (start_i.read())
				{
					data_reg = data_in_bi.read();
					state = 1;
					busy_o.write(false);
				}
				break;
			case 1:
				busy_o.write(true);
				if (clk_count == 1)
				{
					clk_count = 0;
					state = 2;
				} else
				{
					clk_count ++;
				}
				break;			
			case 2:
				if(clk_count > 1)
				{
					sck_o.write(false);
				}
				else
				{
					sck_o.write(true);
				}
				if(clk_count == 0)
				{
					mosi_o.write(data_reg[7]);
				}
				else if(clk_count == 2)
				{
					data_reg = data_reg << 1;
					data_reg[0] = miso_i.read();
				}
				else if(clk_count == 3)
				{					
					if(bit_count == 7)
					{
						state = 0;
						data_out_bo.write(data_reg);
						ready_o.write(true);
						busy_o.write(false);
					}
					bit_count ++;
				}				
				clk_count ++;				
				break;
				
		}
    }
}

void spi_master::demux_block()
{
	if(slave_i.read() == 0)
	{
		ss1_o.write(true);
		ss2_o.write(true);
		ss3_o.write(true);
	}
	else if(slave_i.read() == 1)
	{
		ss1_o.write(false);
		ss2_o.write(true);
		ss3_o.write(true);
	}
	else if(slave_i.read() == 2)
	{
		ss1_o.write(true);
		ss2_o.write(false);
		ss3_o.write(true);
	}
	else if(slave_i.read() == 3)
	{
		ss1_o.write(true);
		ss2_o.write(true);
		ss3_o.write(false);
	}
}