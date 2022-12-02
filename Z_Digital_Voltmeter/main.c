#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include"driverlib/adc.h"
uint32_t potValue[1];
const char Display[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x00};
volatile uint8_t displayColon=1;

void ADC_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE);

    GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);

    ADCSequenceConfigure(ADC0_BASE, 1,
                         ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0,
                             ADC_CTL_CH0);

    ADCSequenceEnable(ADC0_BASE, 1);
}
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
        // Displays the value on 4 digit 7 segment Display
        // digit[0]=1st Digit 7Segment (Left)
        // digit[1]=2nd Digit 7Segment
        // digit[2]=3rd Digit 7Segment
        // digit[3]=4th Digit 7Segment (Right)
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
    // Set the System clock frequency for 40MHz
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    float i=0;
    int voltage=0;
    float actual_voltage=0;
    float temp=0,temp1=0;
    Init();
    SetBrightness(7);
    ADC_Init();
    while(1)
    {
        // Trigger the ADC Block from the CPU
        ADCProcessorTrigger(ADC0_BASE, 1);
        // Receives the data from the ADC Module
        ADCSequenceDataGet(ADC0_BASE, 1, potValue);
        // Stores Analog Value Read by ADC0 of Tiva Microcontroller
        voltage=potValue[0];
        // Converting Raw data to voltage
        temp=33000/4095;
        voltage*=temp;
        voltage/=100;
        //Calculaing the output voltage from voltage divider circuit
        //R1=30K, R2=7.5K used in voltage divider circuit
        temp1=((7.5+30)/7.5);
        actual_voltage=voltage*temp1;
        // Adjustment for displaying on 4 Digit 7 Segment Display
        actual_voltage*=100;
        i=actual_voltage;
        i/=1000;
        if(i!=0)
        {
            i+=4; // 0.4v is being added for accuracy
        }
        i*=10;
        // Display on 7 segment
        Display_Decimal(i,displayColon);
        SysCtlDelay(13333333);

    }
}
