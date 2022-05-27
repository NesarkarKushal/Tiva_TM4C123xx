// Flash Memory Programming

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/fpu.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/flash.h"
uint32_t Data[2];

//char Data[8]="KUSHAL12";

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_4 | SYSCTL_USE_PLL | SYSCTL_XTAL_16MHZ | SYSCTL_OSC_MAIN);

    Data[0]=0xABCD1234;
    Data[1]=0xAABB5555;

    FlashErase(0x20000);// Open Memory browser and add address as 20000 (32 bit Hex TI)
    FlashProgram(Data,0x20000,sizeof(Data));

    SysCtlDelay(1333333);

    while(1)
    {

    }
	return 0;
}
