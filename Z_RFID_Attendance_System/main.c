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
// int check=0;
// int balance_red=100,balance_blue=100;
 int red=0,blue=0;
// char x,y,z,p,q,b;
 int Rahul_Attendance=0;
 int Praveen_Attendance=0;
 int Total_Classes=80;


int main(void)
{
    int x=0;
    uint32_t value=1234.011;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOInput(GPIO_PORTF_BASE,GPIO_PIN_4);
    GPIOPadConfigSet(GPIO_PORTF_BASE,GPIO_PIN_4,GPIO_STRENGTH_8MA,GPIO_PIN_TYPE_STD_WPU);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3);//0X0E


    print_init();
    char *str = i_to_a(value);
    UARTprintf("%s\n",str);
    free(str);
    str = NULL;
    UART_1();
    while(1)
    {
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
                            Rahul_Attendance++;
                            print_init();
                           UARTprintf("Rahul Present\n");
                           UARTprintf("Attended=%d out of %d classes\n",Rahul_Attendance,Total_Classes);



                         }

                            else if(blue==1)
                            {
                                Praveen_Attendance++;
                                print_init();
                               UARTprintf("Praveen Present\n");
                               UARTprintf("Attended=%d out of %d classes\n",Praveen_Attendance,Total_Classes);
                            }

                             else
                             {
                                print_init();
                                UARTprintf("Invalid card\n");
                             }
                         }
                     }
    }
}
