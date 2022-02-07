#include <stdbool.h>
#include <stdint.h>
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include "Nokia_Driver.h"

 uint32_t RX_text[6]={'\0'};
char text;

int main()
{
    int i=0;

    SPI_Init();
    Switch_LED_Init();
    Reset_Init();

  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X10);// RESET PIN =PC4
  SysCtlDelay(13333333);
  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X00);// RESET PIN =PC4
  SysCtlDelay(13333333);
  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X10);// RESET PIN =PC4


  GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);// DC PIN =PC6 = Low to send Command

  GPIOPinWrite(GPIO_PORTC_BASE,0X80,0X80);//Light PCD5110
  SysCtlDelay(13333333);

  while(SSIBusy(SSI3_BASE))
      {

       }

      while(SSIDataGetNonBlocking(SSI3_BASE,&RX_text[0]))
      {

      }

     SSIDataPut(SSI3_BASE,0x21);// Selecting Command Mode of PCD5110
     SSIDataPut(SSI3_BASE,0xC0);//
     SSIDataPut(SSI3_BASE,0x20);// Seleting Command in Basic Mode of PCD5110
     SSIDataPut(SSI3_BASE,0x0C);// PCD5110 To Display result in Normal Mode

     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X40);//DC PIN =PC6= High to send Data
     LcdClear();
     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);//After send is complete DC6=Low

     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X40);//DC PIN =PC6= High to send Data

             Position(0,0);
             LcdString("Hello");
             Position(0,1);
             LcdString("Nokia LCD");
             Position(0,2);
             LcdString("Display");
             Position(0,3);
             LcdString("......");
             SysCtlDelay(13333333);

      GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);// DC PIN =PC6=Low send Complete

     while(1)
     {

     }


}
