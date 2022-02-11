#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<stdlib.h>
#include<string.h>
#include"print.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"


int main()
{
    char str[11]="0001225656";
    uint32_t value=0;

    print_init();
    value=stoa(str);
    UARTprintf("%d\n",value);

    while (1)
    {

    }

}




