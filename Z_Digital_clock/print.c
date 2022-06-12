/*
 * print.c
 *
 *  Created on: Feb 8, 2022
 *      Author: Admin
 */

#include<stdio.h>
#include<stdint.h>

#include<string.h>
#include <stdlib.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
//#include"utils/uartstdio.h"
//#include"utils/uartstdio.c"
void print_init()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_USE_PLL|SYSCTL_OSC_MAIN|SYSCTL_XTAL_16MHZ);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);// ENABLE GPIO PORT A,FOR UART

    GPIOPinConfigure(GPIO_PA0_U0RX); // PA0 IS CONFIGURED TO UART RX
    GPIOPinConfigure(GPIO_PA1_U0TX); // PA1 IS CONFIGURED TO UART TX

    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);

    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(0, 9600, 16000000);

}




void UART_1()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinConfigure(GPIO_PB0_U1RX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinConfigure(GPIO_PB1_U1TX); // PB0 IS CONFIGURED TO UART1 RX
    GPIOPinTypeUART(GPIO_PORTB_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTClockSourceSet(UART1_BASE, UART_CLOCK_PIOSC);
    UARTStdioConfig(1, 9600, 16000000);
}

/*
int no_of_digits(int num)
{
    int digit_count = 0;

    while(num > 0)
    {
        digit_count++;
        num /= 10;
    }

    return digit_count;
}
char *i_to_a(int num)
{
    char *str;
    int digit_count = 0;

    if(num < 0)
    {
        num = -1*num;
        digit_count++;
    }

    digit_count += no_of_digits(num);
    str = malloc(sizeof(char)*(digit_count+1));

    str[digit_count] = '\0';

    while(num > 0)
    {
        str[digit_count-1] = num%10 + '0';
        num = num/10;
        digit_count--;
    }

    if(digit_count == 1)
        str[0] = '-';

    return str;
}
*/
