#include <systemc.h>

#include <all_system.h>

void AllSystem::stimuli()
{  
    rst_n = false; // assert reset
    
    wait(20, SC_NS);
    rst_n = true; // deassert reset
}
