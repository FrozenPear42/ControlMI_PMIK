#ifndef CONTROLMI_PMIK_WS2812_H
#define CONTROLMI_PMIK_WS2812_H

#include <sched.h>

#define CMP_H 5
#define CMP_L 2

void WS2812_rawWriteBuffer(uint16_t* buffer, uint32_t* data, uint32_t offset, uint32_t size);
void WS2812_writeLed(uint16_t* buffer, uint32_t ledNumber, uint8_t r, uint8_t g, uint8_t b);



#endif //CONTROLMI_PMIK_WS2812_H
