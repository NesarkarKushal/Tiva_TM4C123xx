/* Assignment: Using Timer
 * |--------------------------------|
   0----1-------3----4--------------8
         on(2min)        on(4mins)
         _______      ______________
        |       |    |              |
        |       |    |              |
    ____|       |____|              |
     off          off
   (1min)        (1min)

  */
#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"

int i=0;

uint32_t avg=0;
uint64_t one_min=2400000000;/* Freq=40Mhz ,Time delay-->1sec=1*40Mhz therefore
                              1min=60sec & 60sec delay---> 60*40Mhz=2400000000*/
uint64_t oneflag=0;

void Timer0IntHandler(void);

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);


    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);  //TIMER_CFG_PERIODIC

    avg=one_min*5/100;
    TimerLoadSet64(TIMER0_BASE,avg);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0IntHandler);

    while(1)
    {

    }

}


void Timer0IntHandler(void)
{

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);

    oneflag+=avg;
    if(oneflag==one_min)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);

    }
    else if(oneflag==one_min*3)
      {
          GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);

      }
    else if(oneflag==one_min*4)
       {
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
       }
    else if(oneflag==one_min*8)
       {
           GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
           oneflag=0;
       }
}
