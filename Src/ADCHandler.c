#include <ADCHandler.h>
#include <SWO.h>
#include "stm32f3xx_hal.h"


uint16_t ADC_rawPadBuffer[16];
uint8_t ADC_PadBuffer[16];

uint16_t ADC_rawSliderBuffer[8];
uint8_t ADC_SliderBuffer[8];

extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1) {
        SWO_PrintString("ADC1 Conversion completed\r\n");
        for (uint8_t i = 0; i < 11; ++i)
            ADC_PadBuffer[i] = (uint8_t) (((8 + ADC_rawPadBuffer[i]) * 100) / 4096);
    }

    if (hadc->Instance == ADC2) {
        SWO_PrintString("ADC2 Conversion completed\r\n");
        for (uint8_t i = 11; i < 16; ++i)
            ADC_PadBuffer[i] = (uint8_t) (((8 + ADC_rawPadBuffer[i]) * 100) / 4096);
    }

    if (hadc->Instance == ADC3) {
        SWO_PrintString("ADC3 Conversion completed\r\n");
        for (uint8_t i = 0; i < 8; ++i)
            ADC_SliderBuffer[i] = (uint8_t) (((8 + ADC_rawSliderBuffer[i]) * 100) / 4096);
    }
//    char buff[10];
//    SWO_PrintString("Slider ");
//    itoa(i + 1, buff, 10);
//    SWO_PrintString(buff);
//    SWO_PrintString(": ");
//    itoa(adcSliderBuffer[i], buff, 10);
//    SWO_PrintString(buff);
//    SWO_PrintString("\r\n");
}

void ADC_doConversion() {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_rawPadBuffer, 11);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*) (ADC_rawPadBuffer + 11), 5);
    HAL_ADC_Start_DMA(&hadc3, (uint32_t*) (ADC_rawSliderBuffer), 8);
}