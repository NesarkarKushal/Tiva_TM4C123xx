#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"
#include "driverlib/pin_map.h"
#include "driverlib/i2c.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "utils/uartstdio.c"

#define control_reg 0X40
#define device_add (0x90 >>1)

void I2C_Init()
{
        SysCtlPeripheralEnable(SYSCTL_PERIPH_I2C0);
        SysCtlPeripheralReset(SYSCTL_PERIPH_I2C0);
        SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOB);
        GPIOPinConfigure(GPIO_PB3_I2C0SDA);// SDA
        GPIOPinConfigure(GPIO_PB2_I2C0SCL);//SCL
        GPIOPinTypeI2C(GPIO_PORTB_BASE,GPIO_PIN_3 );// SDA
        GPIOPinTypeI2CSCL(GPIO_PORTB_BASE,GPIO_PIN_2);// SCL
        I2CMasterInitExpClk(I2C0_BASE, SysCtlClockGet(), false);

}
void I2C_Write()
{
    I2CMasterSlaveAddrSet(I2C0_BASE, device_add, false);

    I2CMasterDataPut(I2C0_BASE, control_reg);

    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_SEND_START);

    while(I2CMasterBusy(I2C0_BASE));

    I2CMasterSlaveAddrSet(I2C0_BASE, device_add, true);

    I2CMasterDataPut(I2C0_BASE, control_reg);
    I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_BURST_RECEIVE_FINISH);
    while(I2CMasterBusy(I2C0_BASE));

}

uint8_t I2C_Read(uint8_t reg)
{
      I2CMasterSlaveAddrSet(I2C0_BASE, device_add, false);
      I2CMasterDataPut(I2C0_BASE, reg);
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_SEND);
      while(I2CMasterBusy(I2C0_BASE));
      I2CMasterSlaveAddrSet(I2C0_BASE, device_add, true);
      I2CMasterControl(I2C0_BASE, I2C_MASTER_CMD_SINGLE_RECEIVE);
      while(I2CMasterBusy(I2C0_BASE));
      return(I2CMasterDataGet(I2C0_BASE));
}

void InitConsole(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);
    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    UARTClockSourceSet(UART0_BASE, UART_CLOCK_PIOSC);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTStdioConfig(0, 9600, 16000000);
}
int main()
{
    uint32_t PCF8591_Pot=0,PCF8591_LDR=0,PCF8591_Thrmsitor=0,PCF8591_Extpot=0;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);
    I2C_Init();
    InitConsole();
    I2C_Write();
    while(1)
    {
        PCF8591_Pot=I2C_Read(0x00);// onboard pot
        UARTprintf("PCF8591_Pot(A0) = %d\n", PCF8591_Pot);
        SysCtlDelay(40000000/3);
/*
        PCF8591_LDR=I2C_Read(0x01); // onboard LDR
        UARTprintf("PCF8591_LDR(A1) = %d\n", PCF8591_LDR);
        SysCtlDelay(40000000/3);

        PCF8591_Thrmsitor=I2C_Read(0x02); //onboard Thermistor
        UARTprintf("PCF8591_Thrmsitor(A2)= %d\n", PCF8591_Thrmsitor);
        SysCtlDelay(40000000/3);

        PCF8591_Extpot=I2C_Read(0x03); // External Pot connected to AIN3
        UARTprintf("PCF8591_Extpot(A3) = %d\n", PCF8591_Extpot);
        SysCtlDelay(40000000/3);
        UARTprintf("\n\n");
*/

    }
}
