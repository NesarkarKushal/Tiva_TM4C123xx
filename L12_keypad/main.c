
#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/pin_map.h"


#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"

//unsigned char key[16]={'1', '2', '3','A','4','5','6','B','7','8','9','C','*','0','#','D'};

void GPIO_init(void);
void RinCout(void);
void CinRout(void);
void print();

int main(void)
{
    uint8_t check;
//    int i=0;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ); // SYSTEM CLOCK AT 40MHZ
    print();

    while(1)
    {
    RinCout();
    check= GPIOPinRead(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);

    //----------------Row 1 ------------------------------------------------------
    if(check == 0x0E)
    {
        CinRout();
         check=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
        SysCtlDelay(40000000/3);



        if(check == 0xE0)
        {
//            SysCtlDelay(40000000/3);
            UARTprintf("1\n");

        }
       if(check == 0xD0)
       {
//           SysCtlDelay(40000000/3);
           UARTprintf("2\n");
       }
       if(check == 0xB0)
       {
//           SysCtlDelay(40000000/3);
           UARTprintf("3\n");
       }

       if(check == 0x70)
       {
//           SysCtlDelay(40000000/3);
           UARTprintf("A\n");
       }

    }

//-----------------Row 2 -------------------------------------------

    else if(check == 0x0D)
        {
            CinRout();
             check=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
            SysCtlDelay(40000000/3);



            if(check == 0xE0)
            {
//                SysCtlDelay(40000000/3);
                UARTprintf("4\n");
            }
           if(check == 0xD0)
           {
//               SysCtlDelay(40000000/3);
               UARTprintf("5\n");
           }
           if(check == 0xB0)
           {
//              SysCtlDelay(40000000/3);
              UARTprintf("6\n");
            }
           if(check == 0x70)
           {
//               SysCtlDelay(40000000/3);
               UARTprintf("B\n");
           }

        }

//------------------Row 3 ---------------------------------------------

    else if(check == 0x0B)
            {
                 CinRout();
                 check=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
                 SysCtlDelay(40000000/3);

                if(check == 0xE0)
                {
//                    SysCtlDelay(40000000/3);
                    UARTprintf("7\n");
                }
               if(check == 0xD0)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("8\n");
               }
               if(check == 0xB0)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("9\n");
               }

               if(check == 0x70)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("C\n");
               }

            }

// --------------------Row 4 ---------------------------------------

    else if(check == 0x07)
            {
                CinRout();
                 check=GPIOPinRead(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
                SysCtlDelay(40000000/3);

               if(check == 0xE0)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("*\n");
                }

               if(check == 0xD0)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("0\n");
               }

               if(check == 0xB0)
               {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("#\n");
                }

               if(check == 0x70)
                {
//                   SysCtlDelay(40000000/3);
                   UARTprintf("D\n");
                 }
            }


    }
    return 0;
}

void RinCout()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,0X00);


    GPIOPinTypeGPIOInput(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPadConfigSet(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);

}

void CinRout()
{

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3);
    GPIOPinWrite(GPIO_PORTD_BASE,GPIO_PIN_0|GPIO_PIN_1|GPIO_PIN_2|GPIO_PIN_3,0X00);

    GPIOPinTypeGPIOInput(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7);
    GPIOPadConfigSet(GPIO_PORTC_BASE,GPIO_PIN_4|GPIO_PIN_5|GPIO_PIN_6|GPIO_PIN_7,GPIO_STRENGTH_4MA,GPIO_PIN_TYPE_STD_WPU);

}


void print()
{
SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);

}

