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
extern TIM_HandleTypeDef htim6;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {
    if (hadc->Instance == ADC1) {
        for (uint8_t i = 0; i < 11; ++i)
            ADC_PadBuffer[i] = (uint8_t) (((8 + ADC_rawPadBuffer[i]) * 127) / 4096);
    }

    if (hadc->Instance == ADC2) {
        for (uint8_t i = 11; i < 16; ++i)
            ADC_PadBuffer[i] = (uint8_t) (((8 + ADC_rawPadBuffer[i]) * 127) / 4096);
    }

    if (hadc->Instance == ADC3) {
        for (uint8_t i = 0; i < 8; ++i)
            ADC_SliderBuffer[i] = (uint8_t) (((8 + ADC_rawSliderBuffer[i]) * 127) / 4096);
    }

}

void ADC_start() {
    HAL_TIM_Base_Start_IT(&htim6);
}

void ADC_doConversion() {
    HAL_ADC_Start_DMA(&hadc1, (uint32_t*) ADC_rawPadBuffer, 11);
    HAL_ADC_Start_DMA(&hadc2, (uint32_t*) (ADC_rawPadBuffer + 11), 5);
    HAL_ADC_Start_DMA(&hadc3, (uint32_t*) (ADC_rawSliderBuffer), 8);
}