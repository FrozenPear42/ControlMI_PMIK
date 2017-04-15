/**
  ******************************************************************************
  * @file           : usbd_midi_if.h
  * @brief          : Header for usbd_midi_if file.
  ******************************************************************************
*/

#ifndef __USBD_MIDI_IF_H
#define __USBD_MIDI_IF_H

#include <usbd_desc.h>

#ifdef __cplusplus
extern "C" {
#endif

extern USBD_MIDI_ItfTypeDef USBD_MIDI_fops_FS;

extern void sendNoteOn(uint8_t ch, uint8_t note, uint8_t vel);
extern void sendNoteOff(uint8_t ch, uint8_t note);
extern void sendCC(uint8_t ch, uint8_t num, uint8_t value);

#ifdef __cplusplus
}
#endif

#endif /* __USBD_MIDI_IF_H */