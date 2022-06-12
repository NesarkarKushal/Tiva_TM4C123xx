#include<stdint.h>
#include<stdio.h>
#include<stdbool.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include"inc/hw_memmap.h"
#include"inc/hw_types.h"
#include"driverlib/gpio.h"
#include"driverlib/pin_map.h"
#include"driverlib/sysctl.h"
#include "driverlib/eeprom.h"
#include "driverlib/rom.h"
#include "driverlib/rom_map.h"
#include "driverlib/flash.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"
#include "UART.h"

 char data;
 char dest[11];
 uint32_t final[11];
 uint32_t EEPROM_Read[11];
 int i=0;
 int flag=0,j=0;

int main(void)
{
    UART_Init();
    EEPROM_Init();

    while (1)
    {
        while(UARTCharsAvail(UART1_BASE))
        {
            data = UARTCharGet(UART1_BASE); // Apply Breakpoint Here
            dest[i]=data;
            i=i+1;
            UARTCharPut(UART0_BASE,data);//Printing Data on Serial Monitor
            flag=1;
        }

        if(flag==1)
         {
            j=0;
            i=0;
            flag=0;

           for(j=0;j<10;j++)
            {
                final[j]=dest[j+1];
            }

    //Below two lines is to update data in Flash memory at specified Address
//           FlashErase(0x20000);
//           FlashProgram(final,0x20000,sizeof(final));

   //Storing Data in EEPROM Memory
           EEPROMProgram(final,0x0,sizeof(final));
           EEPROMRead(EEPROM_Read,0x0,sizeof(EEPROM_Read)); // Apply Break Point Here

         }
    }
}
