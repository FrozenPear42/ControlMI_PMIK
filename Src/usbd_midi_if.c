#include <usbd_midi.h>
#include <SWO.h>
#include "usbd_midi_if.h"

static uint16_t MIDI_DataRx(uint8_t* msg, uint16_t length);
static uint16_t MIDI_DataTx(uint8_t* msg, uint16_t length);

USBD_MIDI_ItfTypeDef USBD_MIDI_fops_FS =
    {
        MIDI_DataRx,
        MIDI_DataTx
    };

static uint16_t MIDI_DataRx(uint8_t* msg, uint16_t length) {
    uint8_t channel = (uint8_t) (msg[1] & 0xf);
    uint8_t messageType = (uint8_t) (msg[1] & 0xf0);
    uint16_t b = (uint16_t) (((msg[3] & 0x7f) << 7) | (msg[2] & 0x7f));

    uint8_t buff[4];

    itoa(channel, buff, 16);
    SWO_PrintString("Message ");
    SWO_PrintString(buff);
    SWO_PrintString(" type ");
    itoa(messageType, buff, 16);
    SWO_PrintString(buff);
    SWO_PrintString(" data ");
    itoa(b, buff, 16);
    SWO_PrintString(buff);
    SWO_PrintString("\n");

    switch( messageType ) {
        case 0x80:
            break;
        case 0x90:
            break;
        case 0xB0:
            break;
        case 0xC0:
            break;
        case 0xD0:
            break;
        case 0xE0:
            break;
        default:
            break;
    }
    return USBD_OK;
}

static uint16_t MIDI_DataTx(uint8_t* msg, uint16_t length) {
    uint32_t i = 0;
    while( i < length ) {
        APP_Rx_Buffer[APP_Rx_ptr_in] = *(msg + i);
        APP_Rx_ptr_in++;
        i++;
        if( APP_Rx_ptr_in == APP_RX_DATA_SIZE ){
            APP_Rx_ptr_in = 0;
        }
    }
    return USBD_OK;
}

void MIDI_sendNoteOn(uint8_t ch, uint8_t note, uint8_t vel) {
    uint8_t buffer[4];
    buffer[0] = 0x09;
    buffer[1] = (uint8_t) (0x90 | ch);
    buffer[2] = (uint8_t) (0x7f & note);
    buffer[3] = (uint8_t) (0x7f & vel);
    MIDI_DataTx(&buffer[0], 4);
}

void MIDI_sendNoteOff(uint8_t ch, uint8_t note) {
    uint8_t buffer[4];
    buffer[0] = 0x08;
    buffer[1] = (uint8_t) (0x80 | ch);
    buffer[2] = (uint8_t) (0x7f & note);
    buffer[3] = 0;
    MIDI_DataTx(&buffer[0], 4);
}

void MIDI_sendCC(uint8_t ch, uint8_t ccNum, uint8_t value) {
    uint8_t buffer[4];
    buffer[0] = 0x0b;
    buffer[1] = (uint8_t) (0xb0 | ch);
    buffer[2] = (uint8_t) (0x7f & ccNum);
    buffer[3] = (uint8_t) (0x7f & value);
    MIDI_DataTx(&buffer[0], 4);
}