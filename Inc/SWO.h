#ifndef CONTROLMI_PMIK_SWO_H
#define CONTROLMI_PMIK_SWO_H

/*!
 * @file
 * File responsible for writing debug data to SWO
 */

#include <stdint.h>

/*!
 * @brief Sends single character to SWO
 * @param c
 * @return
 */
uint8_t SWO_PrintChar(char c);

/*!
 * Sends a string to SWO
 * @param s
 */
void SWO_PrintString(const char* s);

#endif //CONTROLMI_PMIK_SWO_H_H
