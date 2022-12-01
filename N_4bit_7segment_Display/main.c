#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

const char Display[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
volatile uint8_t displayColon=0;
void Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,0X01);//CLK
    GPIOPinTypeGPIOOutput(GPIO_PORTB_BASE,0X02);//DIO
}

void DelayUsec(unsigned int i)
{
    for(;i>0;i--)
    {
        int j;
        for(j=0;j<500;++j)
        {

        }
    }
}
void clk_high()
{
    GPIOPinWrite(GPIO_PORTB_BASE, 0X01,0X01);//clk=1
//    SysCtlDelay(13333333);
}
void clk_low()
{
    GPIOPinWrite(GPIO_PORTB_BASE, 0X01,0X00);//clk=0
//    SysCtlDelay(13333333);
}
void data_high()
{
    GPIOPinWrite(GPIO_PORTB_BASE, 0X02,0X02);//dio=1
//    SysCtlDelay(13333333);
}
void data_low()
{
    GPIOPinWrite(GPIO_PORTB_BASE, 0X02,0X00);//dio=0
//    SysCtlDelay(13333333);
}
void start()
{
    clk_high();
    data_high();
    DelayUsec(2);
    data_low();
}
void stop()
{
    clk_low();
    DelayUsec(2);
    data_low();
    DelayUsec(2);
    clk_high();
    DelayUsec(2);
    data_high();
}

void ReadResult()
{
    clk_low();
    DelayUsec(5);
    clk_high();
    DelayUsec(2);
    clk_low();
}

void WriteByte(unsigned char b)
{
    int i=0;
    for(i=0;i<8;i++)
    {
        clk_low();
        if(b & 0x01)
        {
            data_high();
        }
        else
        {
            data_low();
        }
        DelayUsec(3);
        b>>=1;
        clk_high();
        DelayUsec(3);
    }
}

void SetBrightness(char brightness)
{
    start();
    WriteByte(0x87+brightness);
    ReadResult();
    stop();
}

void Display_Decimal(int v, int displaySeparator)
{
    unsigned char digit[4];
    int i;
    for(i=0;i<4;i++)
    {
        digit[i]=Display[v%10];
        if(i==2 && displaySeparator)
        {
            digit[i]|=1<<7;
        }
        v/=10;
    }
    start();
    WriteByte(0x40);
    ReadResult();
    stop();

    start();
    WriteByte(0xc0);
    ReadResult();
    int cc;
    for(cc=0;cc<4;++cc)
    {
        WriteByte(digit[3-cc]);
        ReadResult();
    }
    stop();
}

int main()
{
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    int i=0;
    Init();
    SetBrightness(7);
    while(1)
    {
        for(i=0;i<9999;i++)
        {
//            displayColon=!displayColon;
            Display_Decimal(i,displayColon);
            SysCtlDelay(13333333);
        }

    }
}
