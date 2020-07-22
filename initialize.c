/*
 * intialize.c
 *
 *  Created on: November 10, 2019
 *      Author: Pranav Rao
 */
#include <ti/devices/msp432p4xx/driverlib/driverlib.h>
#include "stdio.h"
#include "game.h"
#include "initialize.h"
#include "Timer_HAL.h"

#define PRESSED 0

void initialize()
{
    //init_Launch();
    WDT_A_hold(WDT_A_BASE);
    initHWTimer0();
    init_GPIO();
    init_ADC();
    init_Joystick();
    start_ADC();
}


// Initializing the ADC
void init_ADC()
{
    ADC14_enableModule();
    // This sets the conversion clock to 3MHz
    ADC14_initModule(ADC_CLOCKSOURCE_ADCOSC, ADC_PREDIVIDER_1, ADC_DIVIDER_1,
                     ADC_NOROUTE);
    // This configures the ADC to store output results in ADC_MEM0 up to ADC_MEM1. Each conversion will thus use two channels.
    ADC14_configureMultiSequenceMode(ADC_MEM0, ADC_MEM1, true);
    // This configures the ADC in manual conversion mode. The software will start each conversion.
    ADC14_enableSampleTimer(ADC_AUTOMATIC_ITERATION);
}

// Interfacing the Joy stick with the ADC
void init_Joystick()
{
    // This selects the appropriate GPIO pin as analog input A15 (Joystick X), which is multiplexed on GPIO port P6, pin PIN0
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P6, GPIO_PIN0, GPIO_PRIMARY_MODULE_FUNCTION);
    // This configures ADC_MEM0 to store the result from input channel A15 in non-differential input mode (only a single input pin)
    // The reference for Vref- and Vref+ are VSS and VCC respectively
    ADC14_configureConversionMemory(ADC_MEM0, ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A15, ADC_NONDIFFERENTIAL_INPUTS);

    // TODO: In a manner consistent with what is demonstrated above, configure the appropriate memory address to store the result from Joystick Y.
    ADC14_configureConversionMemory(ADC_MEM1,ADC_VREFPOS_AVCC_VREFNEG_VSS, ADC_INPUT_A9, ADC_NONDIFFERENTIAL_INPUTS);

    // TODO: In a manner consistent with what is demonstrated above, select the GPIO pin for Joystick Y.
    GPIO_setAsPeripheralModuleFunctionInputPin(GPIO_PORT_P4, GPIO_PIN4, GPIO_TERTIARY_MODULE_FUNCTION);
}

void start_ADC()
{
    // Starts the ADC with the first conversion in repeat-mode; subsequent conversions run automatically
    ADC14_enableConversion();
    ADC14_toggleConversionTrigger();
}

void init_GPIO()
{
    // Initialize BoosterPack pushbuttons.
      GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P4, GPIO_PIN4); //joy y
      GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P6, GPIO_PIN0); //joy x
      GPIO_setAsInputPinWithPullUpResistor (GPIO_PORT_P4, GPIO_PIN1); //joystick select


      GPIO_setAsOutputPin(GPIO_PORT_P1, GPIO_PIN0);
      TurnOn_Launch_LED1();
      GPIO_setAsOutputPin(GPIO_PORT_P2, GPIO_PIN6);
      TurnOff_BoosterRed();


      //booster pack button 1
      GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P5, GPIO_PIN1);

      //booster pack button 2
      GPIO_setAsInputPinWithPullUpResistor(GPIO_PORT_P3, GPIO_PIN5);
}

void getSampleJoystick(unsigned *X, unsigned *Y)
{
    *X = ADC14_getResult(ADC_MEM0);
    *Y = ADC14_getResult(ADC_MEM1);
}


char switch_stat_BPT()
{
    return GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1); //get value of S1 to see if it's pressed
}


char switch_stat_BPB()
{
    return GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5); //get value of S2 to see if it was pressed
}

char Boosterpack_PButtonT()
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P5, GPIO_PIN1)) == PRESSED);
}

char Boosterpack_PButtonB()
{
    return ((GPIO_getInputPinValue(GPIO_PORT_P3, GPIO_PIN5)) == PRESSED);
}

char Get_Status_Joystick_Sel()
{
    return GPIO_getInputPinValue(GPIO_PORT_P4, GPIO_PIN1);
}

void TurnOn_Launch_LED1()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void TurnOff_Launch_LED1()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P1, GPIO_PIN0);
}

void TurnOn_BoosterRed()
{
    GPIO_setOutputHighOnPin(GPIO_PORT_P2, GPIO_PIN6);
}
void TurnOff_BoosterRed()
{
    GPIO_setOutputLowOnPin(GPIO_PORT_P2, GPIO_PIN6);
}
