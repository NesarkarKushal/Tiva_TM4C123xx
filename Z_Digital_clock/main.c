#include <stdint.h>
#include <stdbool.h>

#include<stdio.h>
#include<string.h>

#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/timer.h"
#include "LCD.h"
int i=0;

uint32_t avg=0;
//uint64_t one_min=2400000000;/* Freq=40Mhz ,Time delay-->1sec=1*40Mhz therefore
                          //    1min=60sec & 60sec delay---> 60*40Mhz=2400000000*/
uint32_t oneflag=0;
uint64_t onesec=40000000;
uint32_t mins=0;
uint32_t hour=0;
int a2;
void Timer0IntHandler(void);

int main(void)
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_XTAL_16MHZ|SYSCTL_OSC_MAIN);

    LCD_init();
    LCD_Clear(); // Clear the Screen
    SysCtlDelay(13333333);

    LCD_Command(0x0E); //Display ON, Cursor blinking
    SysCtlDelay(13333333);

    LCD_cursorPosition(2,2);// Cursor position
    Display_string("0");
    LCD_cursorPosition(2,4);// Cursor position
    Display_string(":");

    LCD_cursorPosition(2,5);// Cursor position
    Display_string("0");
    LCD_cursorPosition(2,7);// Cursor position
    Display_string(":");

    LCD_cursorPosition(2,8);// Cursor position
    Display_string("0");


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
    if(oneflag==60)
    {
        oneflag=0;
        mins+=1;
        LCD_cursorPosition(2,9);// Cursor position
        Display_string("_");
    }
    else if(mins==60)
    {
        oneflag=0;
        mins=0;
        hour+=1;
        LCD_cursorPosition(2,7);// Cursor position
        Display_string("_");
    }


    unsigned char str[16]="Digital Clock";
    LCD_cursorPosition(1,1);
    Display_string(str);

    char *data_hour = i_to_a(hour);
    LCD_cursorPosition(2,2);// Cursor position
    Display_string(data_hour);
    free(data_hour);
    data_hour = NULL;

    char *data_min = i_to_a(mins);
    LCD_cursorPosition(2,5);// Cursor position
    Display_string(data_min);
    free(data_min);
    data_min = NULL;

    char *data_sec= i_to_a(oneflag);
    LCD_cursorPosition(2,8);// Cursor position
    Display_string(data_sec);
    free(data_sec);
    data_sec = NULL;

}
