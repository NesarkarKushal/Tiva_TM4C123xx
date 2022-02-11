#include<stdio.h>
#include<stdint.h>
#include<stdbool.h>
#include<string.h>
#include"print.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"


int main()
{
    uint32_t value=1234;
    char data[4];
    print_init();
    char *str = i_to_a(value);
    UARTprintf("%s\n",str);
    free(str);
    str = NULL;
    while (1)
    {

    }

}




