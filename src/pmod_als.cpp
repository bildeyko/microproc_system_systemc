#include <systemc.h>
#include <pmod_als.h>
#include <stdio.h>

void Pmod_ALS::input_light()
{
	sensor = 0xA3;
	data_sig.write(sensor);
	printf("**Pmod_ALS - input_light** Sensor new state [ 0x%02X ]\n",  (unsigned char) sensor);
    
    wait(400, SC_NS);
    
    sensor = 0xF1;
	data_sig.write(sensor);
    printf("**Pmod_ALS - input_light** Sensor new state [ 0x%02X ]\n",  (unsigned char) sensor);
	
	wait(500, SC_NS);
	
	sensor = 0x03;
	data_sig.write(sensor);
    printf("**Pmod_ALS - input_light** Sensor new state [ 0x%02X ]\n",  (unsigned char) sensor);
	
	wait(300, SC_NS);
	
	sensor = 0x80;
	data_sig.write(sensor);
    printf("**Pmod_ALS - input_light** Sensor new state [ 0x%02X ]\n",  (unsigned char) sensor);
}