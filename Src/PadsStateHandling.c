//
// Created by Piotr Żelazko on 13.06.2017.
//

#include <usbd_midi_if.h>
#include <MIDI_Consts.hpp>
#include <Menu.h>
#include "ADCHandler.h"
#include "PadsStateHandling.h"

uint8_t PADS_STATES[PADS_NUMBER];

uint8_t Pads_mods[][16] = {
        {0, 1, 2, 3, 4, 5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15}, /* chromatic */
        {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 24, 26}, /* ionian */
        {0, 2, 3, 5, 7, 9, 10, 12, 14, 15, 17, 19, 21, 23, 25, 27}, /* dorian */
        {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 25, 27}, /* phyrigian */
        {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 25, 27}, /* lydian */
        {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 25, 27}, /* myxolidian */
        {0, 2, 4, 5, 7, 9, 11, 12, 14, 16, 17, 19, 21, 23, 25, 27}, /* aeolian */
        {0, 1, 3, 5, 6, 8, 10, 12, 13, 15, 17, 18, 20, 22, 24, 25}, /* locrian */

};

void Pads_Init() {

    for (uint8_t i = 0; i < PADS_NUMBER; ++i)
        PADS_STATES[i] = LOW_UNCHANGED;
}

void update_pads_states() {

    for (uint8_t i = 0; i < PADS_NUMBER; ++i) {

        uint8_t resultingState = 0;
        resultingState |= (ADC_PadBuffer[i] <= 1) ? 0x00 : 0x0F;
        resultingState |= ((PADS_STATES[i] & 0x0F) ^ 0x0F) ? 0xF0 : 0x00;

        PADS_STATES[i] = resultingState;
    }
}


void send_pads_messages() {

    for (uint8_t i = 0; i < PADS_NUMBER; ++i) {

        if (PADS_STATES[i] & 0xF0) { // state changed
            uint8_t velocity;

            if (Menu_velocity != 0)
                velocity = Menu_velocity;
            else
                velocity = (ADC_PadBuffer[i] * 2);

            uint8_t note = 24 + (Menu_selectedOctave * 12) + Menu_selectedKey;
            note  = note + Pads_mods[Menu_selectedScale][15 - i];

            if (PADS_STATES[i] & 0x0F) {
                sendNoteOn(NOTE_CHANNEL, note, velocity);
            } else {
                sendNoteOff(NOTE_CHANNEL, note);
            }
//            PADS_STATES[i] & 0x0F ? sendNoteOn () : sendNoteOff();
        }

    }

}