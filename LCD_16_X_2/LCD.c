/*
 * LCD.c
 *
 *  Created on: Apr 18, 2022
 *      Author: Kushal Nesarkar
 */


#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "string.h"

#define RS GPIO_PIN_0
#define RW GPIO_PIN_1
#define EN GPIO_PIN_2

#define D4 GPIO_PIN_4
#define D5 GPIO_PIN_5
#define D6 GPIO_PIN_6
#define D7 GPIO_PIN_7


void LCD_init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinTypeGPIOOutput(GPIO_PORTA_BASE,D4|D5|D6|D7);//D4,D5,D6,D7

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE,RS|RW|EN);//RS,RW,En

    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(13333333);

    // Init 4 bit

    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);

    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);

    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X30);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);

    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,0X20);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);

    LCD_Command(0x0F);
    }

void LCD_Command(uint8_t c)
{
    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(c & 0xf0));
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);


    GPIOPinWrite(GPIO_PORTD_BASE,RS,!(RS));//RS=0 Instruction/ Command Mode
    GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
    GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(c & 0x0f)<<4);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
    SysCtlDelay(10);
    GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
    SysCtlDelay(50000);
}

void Display_character(unsigned char d)
{
      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d & 0xf0));
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);


      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d & 0x0f)<<4);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);
}

void Display_string(unsigned char *d)
{
      int len=0;
      int i=0;

      for(i=0;d[i]!='\0';i++)
      {
          len++;
      }

      for(i=0;i<len;i++)
      {
      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d[i] & 0xf0));
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);


      GPIOPinWrite(GPIO_PORTD_BASE,RS,RS);//RS=0 Instruction/ Command Mode
      GPIOPinWrite(GPIO_PORTD_BASE,RW,!(RW));//R/W=0 Register Write
      GPIOPinWrite(GPIO_PORTA_BASE,D4|D5|D6|D7,(d[i] & 0x0f)<<4);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,EN);// Enable pin
      SysCtlDelay(10);
      GPIOPinWrite(GPIO_PORTD_BASE,EN,0X00);// Enable pin
      SysCtlDelay(50000);

      }
}

void LCD_Clear()
{
    LCD_Command(0x01);
    SysCtlDelay(10);
}

void LCD_cursorPosition(uint8_t line,uint8_t pos)
{
    if(line==1)
    {
    LCD_Command(0x80 + pos);
    SysCtlDelay(10);
    }
    else
    {
        LCD_Command(0xC0 + pos);
        SysCtlDelay(10);
    }
}
