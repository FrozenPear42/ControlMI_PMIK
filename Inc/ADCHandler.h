#ifndef CONTROLMI_PMIK_ADCHANDLER_H
#define CONTROLMI_PMIK_ADCHANDLER_H

/*!
 * @file
 * @brief Functions in this file are responsible for Analog to Digital Converter.
 * They both initialize them and do the conversion.
 */

#include <inttypes.h>

#define PADS_NUMBER 16

extern uint8_t ADC_PadBuffer[PADS_NUMBER];
extern uint8_t ADC_SliderBuffer[8];


/*!
 * @brief Initializes ADC's
 *
 * This method only starts proper timer to invoke proper interrupt handler.
 */
void ADC_start();

/*!
 * @brief function starts DMA so it reads proper ADC's values into proper buffers so it can be converted later on.
 */
void ADC_doConversion();

#endif //CONTROLMI_PMIK_ADCHANDLER_H
