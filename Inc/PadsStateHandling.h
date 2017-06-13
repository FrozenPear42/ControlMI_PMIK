//
// Created by Piotr Żelazko on 13.06.2017.
//

#ifndef CONTROLMI_PMIK_PADSSTATEHANDLING_H
#define CONTROLMI_PMIK_PADSSTATEHANDLING_H


typedef enum {

    LOW_UNCHANGED =     0x0,
    HIGH_UNCHANGED =    0x0F,
    LOW_CHANGED =       0xF0,
    HIGH_CHANGED =      0xFF,

} PAD_STATE_e;


void Pads_Init();

void update_pads_states();

void send_pads_messages();



#endif //CONTROLMI_PMIK_PADSSTATEHANDLING_H
