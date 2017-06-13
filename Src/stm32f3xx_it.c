/**
  ******************************************************************************
  * @file    stm32f3xx_it.c
  * @brief   Interrupt Service Routines.
  ******************************************************************************
  *
  * COPYRIGHT(c) 2017 STMicroelectronics
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "stm32f3xx_hal.h"
#include "stm32f3xx.h"
#include "stm32f3xx_it.h"
#include "PadsStateHandling.h"

/* USER CODE BEGIN 0 */

#include <WS2812.h>
#include <ADCHandler.h>
#include <Menu.h>
#include <stm32f303xe.h>
#include <SWO.h>
#include <usbd_midi.h>
#include <usbd_midi_if.h>
#include <MIDI_Consts.hpp>

extern TIM_HandleTypeDef htim8;
/* USER CODE END 0 */

/* External variables --------------------------------------------------------*/
extern PCD_HandleTypeDef hpcd_USB_FS;
extern DMA_HandleTypeDef hdma_adc1;
extern DMA_HandleTypeDef hdma_adc2;
extern DMA_HandleTypeDef hdma_adc3;
extern ADC_HandleTypeDef hadc1;
extern ADC_HandleTypeDef hadc2;
extern ADC_HandleTypeDef hadc3;
extern DMA_HandleTypeDef hdma_tim8_ch1;
extern TIM_HandleTypeDef htim1;
extern TIM_HandleTypeDef htim6;
extern TIM_HandleTypeDef htim7;
extern TIM_HandleTypeDef htim20;

/******************************************************************************/
/*            Cortex-M4 Processor Interruption and Exception Handlers         */
/******************************************************************************/

/**
* @brief This function handles System service call via SWI instruction.
*/
void SVC_Handler(void) {
    /* USER CODE BEGIN SVCall_IRQn 0 */

    /* USER CODE END SVCall_IRQn 0 */
    /* USER CODE BEGIN SVCall_IRQn 1 */

    /* USER CODE END SVCall_IRQn 1 */
}

/**
* @brief This function handles Pendable request for system service.
*/
void PendSV_Handler(void) {
    /* USER CODE BEGIN PendSV_IRQn 0 */

    /* USER CODE END PendSV_IRQn 0 */
    /* USER CODE BEGIN PendSV_IRQn 1 */

    /* USER CODE END PendSV_IRQn 1 */
}

/**
* @brief This function handles System tick timer.
*/
void SysTick_Handler(void) {
    /* USER CODE BEGIN SysTick_IRQn 0 */

    /* USER CODE END SysTick_IRQn 0 */
    HAL_IncTick();
    HAL_SYSTICK_IRQHandler();
    /* USER CODE BEGIN SysTick_IRQn 1 */

    /* USER CODE END SysTick_IRQn 1 */
}

/******************************************************************************/
/* STM32F3xx Peripheral Interrupt Handlers                                    */
/* Add here the Interrupt Handlers for the used peripherals.                  */
/* For the available peripheral interrupt handler names,                      */
/* please refer to the startup file (startup_stm32f3xx.s).                    */
/******************************************************************************/

/**
* @brief This function handles EXTI line0 interrupt.
*/
void EXTI0_IRQHandler(void) {
    /* USER CODE BEGIN EXTI0_IRQn 0 */
    MIDI_sendCC(DATA_CHANNEL, CC_PLAY, CC_VALUE_ON);
    /* USER CODE END EXTI0_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_0);
    /* USER CODE BEGIN EXTI0_IRQn 1 */

    /* USER CODE END EXTI0_IRQn 1 */
}

/**
* @brief This function handles EXTI line1 interrupt.
*/
void EXTI1_IRQHandler(void) {
    /* USER CODE BEGIN EXTI1_IRQn 0 */
    Menu_ok();
    /* USER CODE END EXTI1_IRQn 0 */
    HAL_GPIO_EXTI_IRQHandler(GPIO_PIN_1);
    /* USER CODE BEGIN EXTI1_IRQn 1 */
    /* USER CODE END EXTI1_IRQn 1 */
}

/**
* @brief This function handles DMA1 channel1 global interrupt.
*/
void DMA1_Channel1_IRQHandler(void) {
    /* USER CODE BEGIN DMA1_Channel1_IRQn 0 */

    /* USER CODE END DMA1_Channel1_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_adc1);
    /* USER CODE BEGIN DMA1_Channel1_IRQn 1 */
    /* USER CODE END DMA1_Channel1_IRQn 1 */
}

/**
* @brief This function handles ADC1 and ADC2 interrupts.
*/
void ADC1_2_IRQHandler(void) {
    /* USER CODE BEGIN ADC1_2_IRQn 0 */

    /* USER CODE END ADC1_2_IRQn 0 */
    HAL_ADC_IRQHandler(&hadc1);
    HAL_ADC_IRQHandler(&hadc2);
    /* USER CODE BEGIN ADC1_2_IRQn 1 */
    /* USER CODE END ADC1_2_IRQn 1 */
}

/**
* @brief This function handles USB low priority or CAN_RX0 interrupts.
*/
void USB_LP_CAN_RX0_IRQHandler(void) {
    /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 0 */

    /* USER CODE END USB_LP_CAN_RX0_IRQn 0 */
    HAL_PCD_IRQHandler(&hpcd_USB_FS);
    /* USER CODE BEGIN USB_LP_CAN_RX0_IRQn 1 */

    /* USER CODE END USB_LP_CAN_RX0_IRQn 1 */
}

/**
* @brief This function handles TIM1 break and TIM15 interrupts.
*/
void TIM1_BRK_TIM15_IRQHandler(void) {
    /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 0 */

    /* USER CODE END TIM1_BRK_TIM15_IRQn 0 */
    HAL_TIM_IRQHandler(&htim1);
    /* USER CODE BEGIN TIM1_BRK_TIM15_IRQn 1 */

    /* USER CODE END TIM1_BRK_TIM15_IRQn 1 */
}

/**
* @brief This function handles TIM1 update and TIM16 interrupts.
*/
void TIM1_UP_TIM16_IRQHandler(void) {
    /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 0 */

    /* USER CODE END TIM1_UP_TIM16_IRQn 0 */
    HAL_TIM_IRQHandler(&htim1);
    /* USER CODE BEGIN TIM1_UP_TIM16_IRQn 1 */

    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH1, ADC_SliderBuffer[0]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH2, ADC_SliderBuffer[1]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH3, ADC_SliderBuffer[2]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH4, ADC_SliderBuffer[3]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH5, ADC_SliderBuffer[4]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_CH6, ADC_SliderBuffer[5]);
    MIDI_sendCC(DATA_CHANNEL, CC_SLIDER_MAIN, ADC_SliderBuffer[6]);

    update_pads_states();
    send_pads_messages();


    USBD_MIDI_SendPacket();

    /* USER CODE END TIM1_UP_TIM16_IRQn 1 */
}

/**
* @brief This function handles TIM1 trigger, commutation and TIM17 interrupts.
*/
void TIM1_TRG_COM_TIM17_IRQHandler(void) {
    /* USER CODE BEGIN TIM1_TRG_COM_TIM17_IRQn 0 */

    /* USER CODE END TIM1_TRG_COM_TIM17_IRQn 0 */
    HAL_TIM_IRQHandler(&htim1);
    /* USER CODE BEGIN TIM1_TRG_COM_TIM17_IRQn 1 */

    /* USER CODE END TIM1_TRG_COM_TIM17_IRQn 1 */
}

/**
* @brief This function handles TIM1 capture compare interrupt.
*/
void TIM1_CC_IRQHandler(void) {
    /* USER CODE BEGIN TIM1_CC_IRQn 0 */

    /* USER CODE END TIM1_CC_IRQn 0 */
    HAL_TIM_IRQHandler(&htim1);
    /* USER CODE BEGIN TIM1_CC_IRQn 1 */

    /* USER CODE END TIM1_CC_IRQn 1 */
}

/**
* @brief This function handles ADC3 global interrupt.
*/
void ADC3_IRQHandler(void) {
    /* USER CODE BEGIN ADC3_IRQn 0 */

    /* USER CODE END ADC3_IRQn 0 */
    HAL_ADC_IRQHandler(&hadc3);
    /* USER CODE BEGIN ADC3_IRQn 1 */

    /* USER CODE END ADC3_IRQn 1 */
}

/**
* @brief This function handles TIM6 global interrupt and DAC1 underrun interrupt.
*/
void TIM6_DAC_IRQHandler(void) {
    /* USER CODE BEGIN TIM6_DAC_IRQn 0 */
    ADC_doConversion();
    /* USER CODE END TIM6_DAC_IRQn 0 */
    HAL_TIM_IRQHandler(&htim6);
    /* USER CODE BEGIN TIM6_DAC_IRQn 1 */

    /* USER CODE END TIM6_DAC_IRQn 1 */
}

/**
* @brief This function handles TIM7 global interrupt.
*/
void TIM7_IRQHandler(void) {
    /* USER CODE BEGIN TIM7_IRQn 0 */
    HAL_TIM_PWM_Start_DMA(&htim8, TIM_CHANNEL_1, (uint32_t*) WS2812_ledBuffer, (uint16_t) (48 * WS2812_ledCount + 1));
//    ADC_doConversion();
    /* USER CODE END TIM7_IRQn 0 */
    HAL_TIM_IRQHandler(&htim7);
    /* USER CODE BEGIN TIM7_IRQn 1 */

    /* USER CODE END TIM7_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel1 global interrupt.
*/
void DMA2_Channel1_IRQHandler(void) {
    /* USER CODE BEGIN DMA2_Channel1_IRQn 0 */

    /* USER CODE END DMA2_Channel1_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_adc2);
    /* USER CODE BEGIN DMA2_Channel1_IRQn 1 */

    /* USER CODE END DMA2_Channel1_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel3 global interrupt.
*/
void DMA2_Channel3_IRQHandler(void) {
    /* USER CODE BEGIN DMA2_Channel3_IRQn 0 */
    HAL_TIM_PWM_Stop_DMA(&htim8, TIM_CHANNEL_1);
    HAL_TIM_Base_Start_IT(&htim7);
    /* USER CODE END DMA2_Channel3_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_tim8_ch1);
    /* USER CODE BEGIN DMA2_Channel3_IRQn 1 */

    /* USER CODE END DMA2_Channel3_IRQn 1 */
}

/**
* @brief This function handles DMA2 channel5 global interrupt.
*/
void DMA2_Channel5_IRQHandler(void) {
    /* USER CODE BEGIN DMA2_Channel5_IRQn 0 */
    /* USER CODE END DMA2_Channel5_IRQn 0 */
    HAL_DMA_IRQHandler(&hdma_adc3);
    /* USER CODE BEGIN DMA2_Channel5_IRQn 1 */
    /* USER CODE END DMA2_Channel5_IRQn 1 */
}

/**
* @brief This function handles TIM20 break interrupt.
*/
void TIM20_BRK_IRQHandler(void) {
    /* USER CODE BEGIN TIM20_BRK_IRQn 0 */
    /* USER CODE END TIM20_BRK_IRQn 0 */
    HAL_TIM_IRQHandler(&htim20);
    /* USER CODE BEGIN TIM20_BRK_IRQn 1 */

    /* USER CODE END TIM20_BRK_IRQn 1 */
}

/**
* @brief This function handles TIM20 update interrupt.
*/
void TIM20_UP_IRQHandler(void) {
    /* USER CODE BEGIN TIM20_UP_IRQn 0 */
    /* USER CODE END TIM20_UP_IRQn 0 */
    HAL_TIM_IRQHandler(&htim20);
    /* USER CODE BEGIN TIM20_UP_IRQn 1 */

    /* USER CODE END TIM20_UP_IRQn 1 */
}

/**
* @brief This function handles TIM20 trigger and commutation interrupts.
*/
void TIM20_TRG_COM_IRQHandler(void) {
    /* USER CODE BEGIN TIM20_TRG_COM_IRQn 0 */

    /* USER CODE END TIM20_TRG_COM_IRQn 0 */
    HAL_TIM_IRQHandler(&htim20);
    /* USER CODE BEGIN TIM20_TRG_COM_IRQn 1 */

    /* USER CODE END TIM20_TRG_COM_IRQn 1 */
}

/**
* @brief This function handles TIM20 capture compare interrupt.
*/
void TIM20_CC_IRQHandler(void) {
    /* USER CODE BEGIN TIM20_CC_IRQn 0 */
    Menu_processEncoder(TIM20->CNT);
    /* USER CODE END TIM20_CC_IRQn 0 */
    HAL_TIM_IRQHandler(&htim20);
    /* USER CODE BEGIN TIM20_CC_IRQn 1 */

    /* USER CODE END TIM20_CC_IRQn 1 */
}

/* USER CODE BEGIN 1 */

/* USER CODE END 1 */
/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
