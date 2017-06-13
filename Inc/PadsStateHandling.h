//
// Created by Piotr Żelazko on 13.06.2017.
//

#ifndef CONTROLMI_PMIK_PADSSTATEHANDLING_H
#define CONTROLMI_PMIK_PADSSTATEHANDLING_H

/*!
 * @file
 * @brief File responsible for pads states and sending proper messages to the PC.
 */

typedef enum {

    LOW_UNCHANGED =     0x0,
    HIGH_UNCHANGED =    0x0F,
    LOW_CHANGED =       0xF0,
    HIGH_CHANGED =      0xFF,

} PAD_STATE_e;


extern uint8_t Pads_x;
extern uint8_t Pads_y;


/*!
 * @brief Initializes pads states
 *
 * Pads states are initialized to LOW_UNCHANGED state.
 */
void Pads_Init();

/*!
 * Detects states changes.
 */
void update_pads_states();

/*!
 * Sends messages to the PC only in case when a pad changed its state.
 */
void send_pads_messages();



#endif //CONTROLMI_PMIK_PADSSTATEHANDLING_H
