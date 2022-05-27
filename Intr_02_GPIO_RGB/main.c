#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
int data[6]={0x00,0x02,0x00,0x04,0x00,0x08};
int main()
{
    int i=0;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,0X0E);
    while(1)
    {
        for(i=0;i<=5;i++)
        {
         GPIOPinWrite(GPIO_PORTF_BASE, 0X0E,data[i]);
         SysCtlDelay(13333333);
        }

    }
}
