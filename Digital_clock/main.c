#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
//#include "LCD.h"
int i=0;

uint32_t avg=0;
//uint64_t one_min=2400000000;/* Freq=40Mhz ,Time delay-->1sec=1*40Mhz therefore
                          //    1min=60sec & 60sec delay---> 60*40Mhz=2400000000*/
uint64_t oneflag=0;
uint64_t onesec=40000000;
uint32_t mins=0;
uint32_t hour=0;

void Timer0IntHandler(void);

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

//    LCD_init();
//    LCD_Clear(); // Clear the Screen
//    SysCtlDelay(13333333);
//
//    LCD_Command(0x0E); //Display ON, Cursor blinking
//    SysCtlDelay(13333333);
//
//    LCD_Clear(); // Clear the Screen
//    SysCtlDelay(13333333);




    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);  //TIMER_CFG_PERIODIC
    TimerLoadSet64(TIMER0_BASE,onesec);

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

    oneflag+=1;
    //print seconds
//    LCD_cursorPosition(uint8_t 1,uint8_t 2);
//    Display_Digits(oneflag); // Display Integer digits

    if(oneflag==59)
    {
        mins+=1;
        oneflag=0;
//        LCD_cursorPosition(1,2);// Cursor position
//        Display_Digits(mins); // Display Integer digits
//        SysCtlDelay(13333333);
    }
    else if(mins==60)
    {
        mins=0;
        hour+=1;
//        LCD_cursorPosition(1,2);// Cursor position
//        Display_Digits(hour); // Display Integer digits
//        SysCtlDelay(13333333);
    }

}
