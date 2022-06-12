#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/pwm.h"
#include "driverlib/pin_map.h"
#include "inc/tm4c123gh6pm.h"
#include "driverlib/timer.h"

#include"print.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"

 char data;
 char dest[11];
 char User1[11]={'$','0','0','0','9','4','4','6','3','0','1'};
 char User2[11]={'$','0','0','0','9','5','0','4','7','3','4'};
 int i=0;
 int flag=0,j=0;
 int check=0;
 int balance_red=100,balance_blue=100;
 int red=0,blue=0;
 char x,y,z,p,q,b;

 uint32_t avg=0;
 uint64_t one_min=2400000000;
 uint64_t oneflag=0;
 uint64_t one_sec=40000000;
 void Timer0IntHandler(void);
int main(void)
{
    int x=0;
    uint32_t value=1234.011;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3);//0X0E


    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER0);
    TimerConfigure(TIMER0_BASE,TIMER_CFG_PERIODIC_UP);  //TIMER_CFG_PERIODIC

//    avg=one_min*5/100;
    TimerLoadSet64(TIMER0_BASE,one_sec);

    IntEnable(INT_TIMER0A);
    TimerIntEnable(TIMER0_BASE, TIMER_TIMA_TIMEOUT);
    TimerEnable(TIMER0_BASE, TIMER_A);
    TimerIntRegister(TIMER0_BASE,TIMER_A,Timer0IntHandler);



    print_init();
    char *str = i_to_a(value);
    UARTprintf("%s\n",str);
    free(str);
    str = NULL;
    UART_1();
    while(1)
    {

    }
}

void Timer0IntHandler(void)
{

    TimerIntClear(TIMER0_BASE, TIMER_TIMA_TIMEOUT);


    if(data=UARTCharGet(UART1_BASE))
            {
            UARTCharPut(UART0_BASE,data);

               dest[i]=data;
               flag=1;
               i++;
              if(i>12)
             {
                i=0;
                for(j=0;j<10;j++)
                {
                    if(User1[j+1]==dest[j+1])
                    {
                        red=1;
                    }
                    else
                    {
                        red=0;
                    }
                }

                for(j=0;j<10;j++)
                {
                    if(User2[j+1]==dest[j+1])
                    {
                        blue=1;
                     }
                    else
                     {
                        blue=0;
                     }
                 }

                 if(red==1)
                 {
                     print_init();
                    UARTprintf("Rahul Present\n");

                  }

                     else if(blue==1)
                     {
                         print_init();
                        UARTprintf("Praveen Present\n");

                       }

                      else
                      {
                         print_init();
                         UARTprintf("Invalid card\n");
                      }
                  }
              }





  /*  oneflag+=one_sec;
    if(oneflag<one_min*10)
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x08);
    }
    else
    {
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_3, 0x00);
    }
*/

}

