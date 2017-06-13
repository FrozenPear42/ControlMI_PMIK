#ifndef CONTROLMI_PMIK_ADCHANDLER_H
#define CONTROLMI_PMIK_ADCHANDLER_H

#include <inttypes.h>

#define PADS_NUMBER 16

extern uint8_t ADC_PadBuffer[PADS_NUMBER];
extern uint8_t ADC_SliderBuffer[8];

void ADC_start();
void ADC_doConversion();

#endif //CONTROLMI_PMIK_ADCHANDLER_H
