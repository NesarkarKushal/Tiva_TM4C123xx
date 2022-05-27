#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main()
{
    int i=0;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,0X0E);
    while(1)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, 0X0E,0X0E);
        SysCtlDelay(13333333);
        GPIOPinWrite(GPIO_PORTF_BASE, 0X0E,0X00);
        SysCtlDelay(13333333);

    }
}
