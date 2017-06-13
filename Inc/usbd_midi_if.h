#ifndef __USBD_MIDI_IF_H
#define __USBD_MIDI_IF_H

#include <usbd_desc.h>
#include <usbd_midi.h>

/*!
 * @file
 * This file is responsible for sending proper MIDI packets over USB
 */

#ifdef __cplusplus
extern "C" {
#endif

/**
 * External MIIDI Handler
 */
extern USBD_MIDI_ItfTypeDef USBD_MIDI_fops_FS;

/**
 * Sends MIDI Note On command
 * @param ch channel
 * @param note note code
 * @param vel note velocity
 */
void MIDI_sendNoteOn(uint8_t ch, uint8_t note, uint8_t vel);
/**
 * Sends MIDI Note Off command
 * @param ch channel
 * @param note note code
 * @param vel note velocity
 */
void MIDI_sendNoteOff(uint8_t ch, uint8_t note);
/**
 * Sends MIDI CC Command
 * @param ch channel
 * @param num  CC command code
 * @param value CC command value
 */
void MIDI_sendCC(uint8_t ch, uint8_t num, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_MIDI_IF_H */