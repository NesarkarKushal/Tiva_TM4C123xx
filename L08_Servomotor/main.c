#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/pwm.h"
#include "driverlib/pin_map.h"

int main(void)
{
    int i=0;
    volatile uint8_t DutyCycle;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);

    GPIOPinTypePWM(GPIO_PORTB_BASE, GPIO_PIN_4);
    GPIOPinConfigure(GPIO_PB4_M0PWM2);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_1, PWM_GEN_MODE_DOWN);
    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_1,2000);

    PWMOutputState(PWM0_BASE, PWM_OUT_2_BIT, true);
    PWMGenEnable(PWM0_BASE, PWM_GEN_1);
    while(1)
    {
//        SysCtlDelay(6666666*2);
        for(i=0;i<=10;i++)
        {
            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, i*200);
            SysCtlDelay(6666666*2);
        }
        for(i=10;i>=0;i--)
        {

            PWMPulseWidthSet(PWM0_BASE, PWM_OUT_2, i*200);
            SysCtlDelay(6666666*2);
        }

}
	return 0;
}
