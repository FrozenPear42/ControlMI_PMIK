#ifndef CONTROLMI_PMIK_ADCHANDLER_H
#define CONTROLMI_PMIK_ADCHANDLER_H

#include <inttypes.h>

extern uint8_t ADC_PadBuffer[16];
extern uint8_t ADC_SliderBuffer[8];

void ADC_start();
void ADC_doConversion();

#endif //CONTROLMI_PMIK_ADCHANDLER_H
