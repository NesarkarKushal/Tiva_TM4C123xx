/*
 * AT_Command.c
 *
 *  Created on: Oct 8, 2021
 *      Author: Kushal Vishnu Nesarkar
 */

#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include"driverlib/uart.h"
//#include"utils/uartstdio.h"
//#include"utils/uartstdio.c"


void AT()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    SysCtlDelay(13333333);
}

void AT_ROLE_1()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'R');
    UARTCharPut(UART1_BASE,'O');
    UARTCharPut(UART1_BASE,'L');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'1');

    SysCtlDelay(13333333);
}

void AT_RENEW()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'R');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'N');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'W');
    UARTCharPut(UART1_BASE,'?');
    SysCtlDelay(13333333);
}

void AT_IMME_1()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'I');
    UARTCharPut(UART1_BASE,'M');
    UARTCharPut(UART1_BASE,'M');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'1');
    SysCtlDelay(13333333);
}
void AT_Start()
{
   UARTCharPut(UART1_BASE,'A');
   UARTCharPut(UART1_BASE,'T');
   UARTCharPut(UART1_BASE,'+');
   UARTCharPut(UART1_BASE,'S');
   UARTCharPut(UART1_BASE,'T');
   UARTCharPut(UART1_BASE,'A');
   UARTCharPut(UART1_BASE,'R');
   UARTCharPut(UART1_BASE,'T');
   SysCtlDelay(13333333);
}

void AT_Conn()
{
   UARTCharPut(UART1_BASE,'A');
   UARTCharPut(UART1_BASE,'T');
   UARTCharPut(UART1_BASE,'+');
   UARTCharPut(UART1_BASE,'C');
   UARTCharPut(UART1_BASE,'O');
   UARTCharPut(UART1_BASE,'N');
   SysCtlDelay(13333333);
}

void AT_Connl()
{
   UARTCharPut(UART1_BASE,'A');
   UARTCharPut(UART1_BASE,'T');
   UARTCharPut(UART1_BASE,'+');
   UARTCharPut(UART1_BASE,'C');
   UARTCharPut(UART1_BASE,'O');
   UARTCharPut(UART1_BASE,'N');
   UARTCharPut(UART1_BASE,'N');
   UARTCharPut(UART1_BASE,'L');
   SysCtlDelay(13333333);

}

void AT_IMME_0()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'I');
    UARTCharPut(UART1_BASE,'M');
    UARTCharPut(UART1_BASE,'M');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'0');
    SysCtlDelay(13333333);
}

void AT_RESET()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'R');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'S');
    UARTCharPut(UART1_BASE,'E');
    UARTCharPut(UART1_BASE,'T');
    SysCtlDelay(13333333);
}

void AT_DISC()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'D');
    UARTCharPut(UART1_BASE,'I');
    UARTCharPut(UART1_BASE,'S');
    UARTCharPut(UART1_BASE,'C');
    UARTCharPut(UART1_BASE,'?');
    SysCtlDelay(13333333);
}
void AT_ADDR()
{
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'T');
    UARTCharPut(UART1_BASE,'+');
    UARTCharPut(UART1_BASE,'A');
    UARTCharPut(UART1_BASE,'D');
    UARTCharPut(UART1_BASE,'D');
    UARTCharPut(UART1_BASE,'R');
    UARTCharPut(UART1_BASE,'?');
    SysCtlDelay(13333333);
}

