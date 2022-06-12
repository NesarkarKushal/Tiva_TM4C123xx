/*
 * UART.c
 *
 *  Created on: Feb 9, 2022
 *      Author: Admin
 */


#include<stdint.h>
#include<stdbool.h>
#include <math.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include "driverlib/eeprom.h"

#include"driverlib/uart.h"


void UART_Init()
{
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

}

void EEPROM_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_EEPROM0);

       SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
       GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE , GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3);

       while(EEPROMInit()==EEPROM_INIT_ERROR)
       {
                   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2 | GPIO_PIN_3, 0x02);
                   SysCtlDelay(13333333);

                   GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2| GPIO_PIN_3, 0x00);
                   SysCtlDelay(13333333);
       }

}

