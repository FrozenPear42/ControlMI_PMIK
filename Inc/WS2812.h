#ifndef CONTROLMI_PMIK_WS2812_H
#define CONTROLMI_PMIK_WS2812_H

#include <sched.h>

#define CMP_H 12
#define CMP_L 2

#define WS2812_BUFFSIZE 512

extern uint16_t WS2812_ledBuffer[WS2812_BUFFSIZE];
extern uint16_t WS2812_ledCount;

void WS2812_start(uint16_t ledCount);

void WS2812_rawWriteBuffer(uint32_t* data, uint32_t offset, uint32_t size);

void WS2812_writeLed(uint32_t ledNumber, uint8_t r, uint8_t g, uint8_t b);

#endif //CONTROLMI_PMIK_WS2812_H
