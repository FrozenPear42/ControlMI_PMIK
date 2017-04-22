#include <WS2812.h>
#include <stm32f3xx_hal.h>

uint16_t WS2812_ledBuffer[WS2812_BUFFSIZE];
uint16_t WS2812_ledCount;

extern TIM_HandleTypeDef htim7;


void WS2812_start(uint16_t ledCount) {
    WS2812_ledCount = ledCount;
    for (uint16_t i = 0; i < ledCount; ++i)
        WS2812_writeLed(i, 0x00, 0x00, 0x00);

    HAL_TIM_Base_Start_IT(&htim7);
}

void WS2812_rawWriteBuffer(uint32_t* data, uint32_t offset, uint32_t size) {
    uint32_t x;
    for (x = 0; x < size; ++x) {
        WS2812_ledBuffer[((x + offset) * 8) + 0] = (uint16_t) ((data[x] & 0x80) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 1] = (uint16_t) ((data[x] & 0x40) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 2] = (uint16_t) ((data[x] & 0x20) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 3] = (uint16_t) ((data[x] & 0x10) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 4] = (uint16_t) ((data[x] & 0x08) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 5] = (uint16_t) ((data[x] & 0x04) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 6] = (uint16_t) ((data[x] & 0x02) ? CMP_H : CMP_L);
        WS2812_ledBuffer[((x + offset) * 8) + 7] = (uint16_t) ((data[x] & 0x01) ? CMP_H : CMP_L);
    }
}

void WS2812_writeLed(uint32_t ledNumber, uint8_t r, uint8_t g, uint8_t b) {
    WS2812_rawWriteBuffer((uint32_t*) &g, ledNumber + 0, 1);
    WS2812_rawWriteBuffer((uint32_t*) &r, ledNumber + 1, 1);
    WS2812_rawWriteBuffer((uint32_t*) &b, ledNumber + 2, 1);
}