//
// Created by Piotr Żelazko on 13.06.2017.
//

#include <usbd_midi_if.h>
#include "ADCHandler.h"
#include "PadsStateHandling.h"

uint8_t PADS_STATES [PADS_NUMBER];

void Pads_Init (){

    for (uint8_t i = 0; i < PADS_NUMBER; ++i)
        PADS_STATES[i] = LOW_UNCHANGED;
}

void update_pads_states() {

    for (uint8_t i  = 0; i < PADS_NUMBER; ++i){

        uint8_t resultingState = 0;
        resultingState |= (ADC_PadBuffer[i] == 0x00) ? 0x00 : 0x0F;
        resultingState |= ((PADS_STATES[i] & 0x0F) ^ 0x0F) ?  0xF0 : 0x00;

        PADS_STATES[i] = resultingState;

    }

}


void send_pads_messages(){

    for (uint8_t i  = 0; i < PADS_NUMBER; ++i){

        if (PADS_STATES[i] & 0xF0){ // state changed
// TODO : fill arguments
//            PADS_STATES[i] & 0x0F ? sendNoteOn () : sendNoteOff();
        }

    }

}