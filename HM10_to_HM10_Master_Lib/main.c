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
#include "AT_Command.h"
int main(void)
{

    int x=0;
    char data,Tx_data;

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

    AT();
    SysCtlDelay(13333333);
    AT_RESET();
    SysCtlDelay(13333333);
    AT_IMME_0();
    SysCtlDelay(13333333);
    AT_Start();
    SysCtlDelay(13333333);
    AT_ROLE_1();
    SysCtlDelay(13333333);

    while (1)
    {
        char data_1;
        if(UARTCharsAvail(UART1_BASE))
        {
            data_1= UARTCharGet(UART1_BASE);
            SysCtlDelay(13333333);
            UARTCharPut(UART0_BASE,data_1);
        }
        if(UARTCharsAvail(UART0_BASE))
        {
            Tx_data = UARTCharGet(UART0_BASE);
            UARTCharPut(UART1_BASE,Tx_data);
            UARTCharPut(UART0_BASE,Tx_data);
            SysCtlDelay(13333333);
        }

    }
}
