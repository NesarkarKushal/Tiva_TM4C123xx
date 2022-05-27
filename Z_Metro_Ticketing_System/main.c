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

 void recharge(char x)
 {
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3, 0x02);
                SysCtlDelay(13333333);
                GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3, 0x00);
                SysCtlDelay(13333333);
                print_init();
                UARTprintf("Recharing the Card\n");
//                UARTprintf("Select the user\n");
//                x=UARTCharGet(UART0_BASE);
//                UARTprintf("user=%c\n",x);
                if(x=='1')
                {
                    UARTprintf("Select the plan for Red Card\n");
                    UARTprintf("Rs=100---> A\n");
                    UARTprintf("Rs=200---> B\n");
                    UARTprintf("Rs=300---> C\n");
                    UARTprintf("Rs=400---> D\n");
                    y=UARTCharGet(UART0_BASE);
                    UARTprintf("y=%c\n",y);
                    switch (y)
                     {
                        case 'A': balance_red=100;
                                  break;
                        case 'B': balance_red=200;
                                  break;
                        case 'C': balance_red=300;
                                  break;
                        case 'D': balance_red=400;
                                  break;
                        default: balance_red=-1;
                                  break;
                      }
                    UARTprintf("Recharged: Red card New Balance=%d\n",balance_red);

                }
                else if(x=='2')
                {
                    UARTprintf("Select the plan for Blue Card\n");
                    UARTprintf("Rs=100---> A\n");
                    UARTprintf("Rs=200---> B\n");
                    UARTprintf("Rs=300---> C\n");
                    UARTprintf("Rs=400---> D\n");
                    z=UARTCharGet(UART0_BASE);
                    UARTprintf("z=%c\n",z);
                    switch (z)
                    {
                      case 'A': balance_blue=100;
                                break;
                      case 'B': balance_blue=200;
                                break;
                      case 'C': balance_blue=300;
                                break;
                      case 'D': balance_blue=400;
                                break;
                      default: balance_blue=-1;
                                break;
                     }
                   UARTprintf("Recharged:Blue card New Balance=%d\n",balance_blue);

                }
                else
                {
                    UARTprintf("User Not Found\n");
                }

            }
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

                print_init();
                balance_red-=20;
                char *str1 = i_to_a(balance_red);
                UARTprintf("Remaining balance_red=%s\n",str1);
                free(str1);
                str1 = NULL;
                if(balance_red<30)
                {
                  UARTprintf("Red card Balance is Low\n");
                  UARTprintf("Do you want to recharge:\n");
                  UARTprintf("Yes=Y and No=N:\n");
                  UARTprintf("N=your card will be blocked Temporarily:\n");
                  p=UARTCharGet(UART0_BASE);
                  switch(p)
                  {
                  case 'Y':b='1';
                           recharge(b);
                           break;

                  case 'N':UARTprintf("Your card is Blocked Please Unlock it!:\n");
                           break;
                  }


                }

                }
                 else if(blue==1)
                 {

                   print_init();
                   balance_blue-=20;

                   char *str2 = i_to_a(balance_blue);
                   UARTprintf("Remaining balance_blue=%s\n",str2);
                   free(str2);
                   str2 = NULL;
                   if(balance_blue<30)
                   {
                       UARTprintf("Blue card Balance is Low\n");
                       UARTprintf("Do you want to recharge:\n");
                       UARTprintf("Yes=Y and No=N:\n");
                       UARTprintf("N=your card will be blocked Temporarily:\n");
                       q=UARTCharGet(UART0_BASE);
                       switch(q)
                       {
                         case 'Y':b='2';
                                  recharge(b);
                                  break;

                         case 'N':UARTprintf("Your card is Blocked Please Unlock it!:\n");
                                  break;
                        }
                   }

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

