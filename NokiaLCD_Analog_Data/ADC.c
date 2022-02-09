/*
 * ADC.c
 *
 *  Created on: Jan 28, 2022
 *      Author: Admin
 */


#include<stdint.h>
#include<stdbool.h>
#include"inc/hw_memmap.h"
#include"driverlib/gpio.h"
#include"inc/hw_types.h"
#include"driverlib/debug.h"
#include"driverlib/sysctl.h"
#include"driverlib/adc.h"

uint32_t potValue[1];

void ADC_Init()
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0); // ENABLE ADC0 MODULE

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // ENABLE GPIO for ADC0 Module

    GPIOPinTypeADC(GPIO_PORTE_BASE,GPIO_PIN_3);// ENABLE AN0 OF ADC0 MODULE

    ADCSequenceConfigure(ADC0_BASE, 1, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 1, 0, ADC_CTL_CH0);

// ENABLE THE SEQUENCE 1 FOR ADC0
    ADCSequenceEnable(ADC0_BASE, 1);
}

uint32_t ADC_Get()
{
    ADCProcessorTrigger(ADC0_BASE, 1);

// STORE THE CONVERTED VALUE FOR ALL DIFFERENT SAMPLING IN ARRAY
//ui32ADC0Value
    ADCSequenceDataGet(ADC0_BASE, 1, potValue);
    return potValue;

}
