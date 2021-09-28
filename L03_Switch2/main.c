#include <stdbool.h>
#include <stdint.h>

#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"

#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5 | SYSCTL_USE_PLL | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
        GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE,GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

        GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_0);
        HWREG(GPIO_PORTF_BASE + GPIO_O_LOCK) = GPIO_LOCK_KEY;
        HWREG(GPIO_PORTF_BASE + GPIO_O_CR) |= 0x01;
        GPIOPadConfigSet(GPIO_PORTF_BASE, GPIO_PIN_0,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);

        while(1)
        {
            if(!GPIOPinRead(GPIO_PORTF_BASE,GPIO_PIN_0))
               {
                     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x04);
                     SysCtlDelay(13333333);
                     GPIOPinWrite(GPIO_PORTF_BASE,GPIO_PIN_2,0x00);
                     SysCtlDelay(13333333);
               }
        }
	return 0;
}
