#include <stdio.h>

#include <all_system.h>
#include <cpu_sw_dindout.h>
#include <cpu_sw_periph.h>

void cpu_main()
{
    unsigned short ready;
	unsigned char light_lvl;
    unsigned short leds_mask, leds;
	
    printf("Software started!\n");

    while (1)
    {
		periph_set_start(0x1);
		
		ready =  periph_get_ready();
		if(ready == 1)
		{
			light_lvl = periph_get_data();
			printf("**periph_controller - execute_write** Light level [ 0x%02X ]\n", light_lvl);
			
			leds_mask = 0xFFFF;
			leds = 16 * light_lvl/255;
			leds_mask = leds_mask >> (16 - leds);
			
			printf("**periph_controller - execute_write** Leds output [ 0x%04X ]\n", leds_mask);
			dout_write(leds_mask);
		}
    }
}
