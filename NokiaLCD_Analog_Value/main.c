/*  Connection of Nokia LCD display

   LED       ==> PC7
   SCLK      ==> PD0
   DN-(MOSI) ==> PD3
   D/C       ==> PC6
   RST       ==> PC4
   SCE       ==> PC5
   GND       ==> GND
   VCC       ==> +3.3V

*/
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include<stdlib.h>
#include "driverlib/sysctl.h"
#include "driverlib/ssi.h"
#include "driverlib/interrupt.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "inc/hw_memmap.h"
#include"driverlib/adc.h"

#include"print.h"
#include"driverlib/uart.h"
#include"utils/uartstdio.h"
#include"utils/uartstdio.c"
#include "Nokia_Driver.h"
#include "ADC.h"
//#include "UART.h"



//#define atoa(x) #x

 uint32_t RX_text[6]={'\0'};
 uint32_t ADC_Value[1];
char buf[4];

char text;

int main()
{

    int i=0;
    int Sata=0;

    SPI_Init();
    Switch_LED_Init();
    Reset_Init();
    ADC_Init();
    print_init();



  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X10);// RESET PIN =PC4
  SysCtlDelay(13333333);
  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X00);// RESET PIN =PC4
  SysCtlDelay(13333333);
  GPIOPinWrite(GPIO_PORTC_BASE,0X10,0X10);// RESET PIN =PC4


  GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);// DC PIN =PC6

  GPIOPinWrite(GPIO_PORTC_BASE,0X80,0X80);//Light Nokia
  SysCtlDelay(13333333);
//  GPIOPinWrite(GPIO_PORTC_BASE,0X80,0X00);//Light Nokia
//  SysCtlDelay(13333333);


//  GPIOPinWrite(GPIO_PORTC_BASE,0X20,0X20);// (SCE)CHip select PIN =PC5
//  SysCtlDelay(13333333);
//
  while(SSIBusy(SSI3_BASE))
      {

       }

      while(SSIDataGetNonBlocking(SSI3_BASE,&RX_text[0]))
      {

      }

     SSIDataPut(SSI3_BASE,0x21);
     SSIDataPut(SSI3_BASE,0xC0);
     SSIDataPut(SSI3_BASE,0x20);
     SSIDataPut(SSI3_BASE,0x0C);

     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X40);
     LcdClear();
     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);

     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X40);// DC PIN =PC6

             Position(0,0);
             LcdString("Analog Data =");
             Position(0,1);
             char data[3]="KUS";
             LcdString(data);

      SysCtlDelay(13333333);

         GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);// DC PIN =PC6


//
//     while(1)
//     {
//         ADCProcessorTrigger(ADC0_BASE, 1);
//         ADCSequenceDataGet(ADC0_BASE, 1, ADC_Value);
//
//     }


  while(1)
  {

      while(SSIBusy(SSI3_BASE))
      {

       }

      while(SSIDataGetNonBlocking(SSI3_BASE,&RX_text[0]))
      {

      }
        GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X40);// DC PIN =PC6

        while(1)
        {
         ADCProcessorTrigger(ADC0_BASE, 1);
         ADCSequenceDataGet(ADC0_BASE, 1, ADC_Value);

         Sata=ADC_Value[0];
         char *str = i_to_a(Sata);
         UARTprintf("%s\n",str);
         Position(0,1);
         LcdString(str);
         SysCtlDelay(13333);


             free(str);
             str = NULL;

        }

     GPIOPinWrite(GPIO_PORTC_BASE,0X40,0X00);// DC PIN =PC6

      }


}
