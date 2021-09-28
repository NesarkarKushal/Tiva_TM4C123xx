#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int c1,c2,i;

//char buf1,buf2;

//int val[10]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x67};

int h[10]={0x30,0x00,0x50,0x40,0x60,0x60,0x70,0x00,0x70,0x60}; //for higher nibble
int l[10]={0x0F,0x06,0x0B,0x0F,0x06,0x0D,0x0D,0x07,0x0F,0x07}; // for lower nibble


int main(void)
{

    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // SYSTEM CLOCK AT 40MHZ

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);


    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);//E,F,G,Dec
    GPIOPinTypeGPIOOutput(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);//A,B,C,D

    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0,0x01);

    while(1)
    {
        for(i=0;i<10;i++)
        {

        c1= ~l[i]; //LOWER NIBBLE
         // buf1=~c1;

        c2=~h[i];//HIGHER NIBBLE
        //buf2=~c2;

        GPIOPinWrite(GPIO_PORTE_BASE, GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,c1);
        GPIOPinWrite(GPIO_PORTA_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,c2);
        SysCtlDelay(20000000);


        }

    }
    return (0);
}
