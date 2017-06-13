#ifndef CONTROLMI_PMIK_WS2812_H
#define CONTROLMI_PMIK_WS2812_H

/*!
 * @file
 * File responsible for communicating with WS2812 LED's.
 */

#include <sched.h>

#define CMP_H 12
#define CMP_L 2

#define WS2812_BUFFSIZE 1024

extern uint16_t WS2812_ledBuffer[WS2812_BUFFSIZE];
extern uint16_t WS2812_ledCount;


/*!
 * @brief Initializes LED's
 * @param ledCount number of LED's being used in application
 */
void WS2812_start(uint16_t ledCount);

/*!
 * Reads data from buffer into destination buffer so the LED's give the proper colour.
 * @param data
 * @param offset
 * @param size
 */
void WS2812_rawWriteBuffer(uint32_t *data, uint32_t offset, uint32_t size);


/*!
 * Writes a RGB colour into a selected LED.
 * @param ledNumber LED's to which the colour is being written
 * @param r RED value
 * @param g GREEN value
 * @param b BLUE value
 */
void WS2812_writeLed(uint32_t ledNumber, uint8_t r, uint8_t g, uint8_t b);

#endif //CONTROLMI_PMIK_WS2812_H
