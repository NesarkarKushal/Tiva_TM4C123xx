
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"

void GPIO_interrupt(void)
{
    GPIOIntClear(GPIO_PORTF_BASE, GPIO_PIN_4);

      if(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_4))
        {
              GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x04);
              SysCtlDelay(13333333);
              GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x00);
              SysCtlDelay(13333333);
        }

}

int main(void)
{
     SysCtlClockSet(SYSCTL_SYSDIV_8|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // SYSTEM CLOCK AT 40MHZ
     SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

     GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_2);
     GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
     GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);

    IntEnable(INT_GPIOF);
    GPIOIntEnable(GPIO_PORTF_BASE, GPIO_PIN_4);

    GPIO_interrupt();

    return 0;
}


