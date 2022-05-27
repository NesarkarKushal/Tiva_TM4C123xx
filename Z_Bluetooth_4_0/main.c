#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"

int main(void)
{

    int i=0;
    char data;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinConfigure(GPIO_PB1_U1TX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(1, 9600, 16000000);


    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_1);//3 pin Output pins


    while (1)
    {
        if(UARTCharsAvail(UART1_BASE))
        {
            data = UARTCharGet(UART1_BASE);

            UARTCharPut(UART0_BASE,data);
//            SysCtlDelay(13333333);
        }
        if(data=='H')
         {
           GPIOPinWrite(GPIO_PORTF_BASE, 0X0E, GPIO_PIN_1); //LED ON
           SysCtlDelay(13333333);//Delay 1sec
          }
         else if(data=='L')
         {
           GPIOPinWrite(GPIO_PORTF_BASE, 0X0E, !(GPIO_PIN_1)); //LED OFF
           SysCtlDelay(13333333); //Delay 1sec
          }
    }
}
