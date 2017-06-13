#ifndef CONTROLMI_PMIK_SWO_H
#define CONTROLMI_PMIK_SWO_H

/*!
 * @file
 * @brief File responsible for writing debug data to SWO
 */

#include <stdint.h>

/*!
 * @brief Sends single character to SWO
 * @param c character
 * @return
 */
uint8_t SWO_PrintChar(char c);

/*!
 * Sends a string to SWO
 * @param s string
 */
void SWO_PrintString(const char* s);

#endif //CONTROLMI_PMIK_SWO_H_H
