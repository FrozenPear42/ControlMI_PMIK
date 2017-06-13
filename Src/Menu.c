//
// Created by Wojciech on 12.06.2017.
//
#include <Menu.h>
#include <SSD1306.h>
#include <usbd_midi_if.h>
#include <MIDI_Consts.hpp>
#include <SWO.h>

SSD1306_Dev* Menu_display;

#define MENU_MAIN 0
#define MENU_SCALE 1
#define MENU_KEY 2
#define MENU_OCTAVE 3
#define MENU_CHANNEL_SELECT 4

uint8_t Menu_state;
uint8_t Menu_selectedItem;
uint8_t Menu_page;

char** Menu_strings;
uint8_t Menu_items;

uint32_t Menu_encoderCount;

uint8_t Menu_selectedScale;
uint8_t Menu_selectedKey;
uint8_t Menu_selectedOctave;
uint8_t Menu_velocity;

#define MENU_MAIN_ITEMS 4
#define MENU_MAIN_BOX 0
#define MENU_MAIN_SCALES 1
#define MENU_MAIN_KEYS 2
#define MENU_MAIN_OCTAVE 3


char* Menu_mainStrings[] = {
        "Box",
        "Scale",
        "Key",
        "Octave",
};

#define MENU_SCALE_ITEMS 8
char* Menu_scaleStrings[] = {
        "Chromatic",
        "Ionian",
        "Dorian",
        "Phyrigian",
        "Lydian",
        "Mixolydian",
        "Aeolian",
        "Locrian"
};

#define MENU_KEY_ITEMS 12
char* Menu_keyStrings[] = {
        "C",
        "C#",
        "D",
        "D#",
        "E",
        "F",
        "F#",
        "G",
        "G#",
        "A",
        "A#",
        "B"
};

#define MENU_OCTAVE_ITEMS 7
char* Menu_octaveStrings[] = {
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6"
};

static uint8_t Menu_arrowGlyph[16] = {
        0x00, /* 00000000 */
        0x40, /* 01000000 */
        0x60, /* 01100000 */
        0x70, /* 01110000 */
        0x78, /* 01111000 */
        0x7c, /* 01111100 */
        0x7e, /* 01111110 */
        0x7c, /* 01111100 */
        0x78, /* 01111000 */
        0x70, /* 01110000 */
        0x60, /* 01100000 */
        0x40, /* 01000000 */
        0x00, /* 00000000 */
        0x00, /* 00000000 */
        0x00, /* 00000000 */
        0x00, /* 00000000 */
};


void Menu_init(SSD1306_Dev* display) {
    Menu_display = display;
    Menu_encoderCount = 0;
    Menu_velocity = 0;
    Menu_selectedOctave = 4;
    Menu_selectedScale = 0;
    Menu_selectedKey = 0;

    Menu_changeState(MENU_MAIN);
    Menu_redraw(1);
}

void Menu_processEncoder(uint32_t value) {
    if (Menu_encoderCount != value / 4) {
        if (Menu_encoderCount < value / 4) {
            Menu_left();
        } else {
            Menu_right();
        }
        Menu_encoderCount = value / 4;
    }

}


void Menu_left() {

    switch (Menu_state) {
        case MENU_CHANNEL_SELECT:
            MIDI_sendCC(DATA_CHANNEL, CC_NAV_LEFT, CC_VALUE_ON);
            break;
        default:
            if (Menu_selectedItem != 0)
                --Menu_selectedItem;
            Menu_redraw(0);
            break;
    }
}


void Menu_right() {
    switch (Menu_state) {
        case MENU_CHANNEL_SELECT:
            MIDI_sendCC(DATA_CHANNEL, CC_NAV_RIGHT, CC_VALUE_ON);
            break;
        default:
            if (Menu_selectedItem < Menu_items - 1)
                ++Menu_selectedItem;
            Menu_redraw(0);
            break;

    }
}


void Menu_ok() {
    switch (Menu_state) {
        case MENU_MAIN:
            if (Menu_selectedItem == MENU_MAIN_SCALES) {
                Menu_changeState(MENU_SCALE);
            } else if (Menu_selectedItem == MENU_MAIN_KEYS) {
                Menu_changeState(MENU_KEY);
            } else if (Menu_selectedItem == MENU_MAIN_OCTAVE) {
                Menu_changeState(MENU_OCTAVE);
            } else if (Menu_selectedItem == MENU_MAIN_BOX) {
                Menu_changeState(MENU_CHANNEL_SELECT);
            }
            break;

        case MENU_CHANNEL_SELECT:
            Menu_changeState(MENU_MAIN);
            break;

        case MENU_SCALE:
            Menu_selectedScale = Menu_selectedItem;
            Menu_changeState(MENU_MAIN);
            break;

        case MENU_KEY:
            Menu_selectedKey = Menu_selectedItem;
            Menu_changeState(MENU_MAIN);
            break;


        case MENU_OCTAVE:
            Menu_selectedOctave = Menu_selectedItem;
            Menu_changeState(MENU_MAIN);
            break;


        default:
            HAL_GPIO_TogglePin(LD3_GPIO_Port, LD3_Pin);
            break;
    }
}


void Menu_redraw(uint8_t force) {

    switch (Menu_state) {
        case MENU_MAIN:
        case MENU_SCALE:
        case MENU_KEY:
        case MENU_OCTAVE:
            SSD1306_drawString(Menu_display, 0, 0, "CONTROL MI PMIK", 16);

            SSD1306_drawChar(Menu_display, 0, 16, ' ');
            SSD1306_drawChar(Menu_display, 0, 32, ' ');
            SSD1306_drawChar(Menu_display, 0, 48, ' ');
            SSD1306_drawGlyph(Menu_display, 0, 16 * (1 + Menu_selectedItem % 3), Menu_arrowGlyph);

            if (Menu_page != Menu_selectedItem / 3 || force == 1) {
                Menu_page = Menu_selectedItem / 3;
                for (int i = 0; i < 3; ++i) {
                    if (Menu_page * 3 + i < Menu_items)
                        SSD1306_drawString(Menu_display, 8, 16 * (i + 1), Menu_strings[Menu_page * 3 + i], 15);
                    else
                        SSD1306_drawString(Menu_display, 8, 16 * (i + 1), "               ", 15);
                }
            }
            break;
        case MENU_CHANNEL_SELECT:
            SSD1306_drawString(Menu_display, 0,  0, "CHANNEL SELECT", 16);
            SSD1306_drawString(Menu_display, 0, 16, "USE ENCODER TO", 16);
            SSD1306_drawString(Menu_display, 0, 32, "MOVE BOX", 16);
            SSD1306_drawString(Menu_display, 0, 48, "OK TO EXIT", 16);

            break;
        default:
            SSD1306_drawString(Menu_display, 0, 0, "WRONG STATE XD", 16);
            break;
    }

}

void Menu_changeState(int state) {
    Menu_page = 0;
    Menu_selectedItem = 0;
    switch (state) {
        case MENU_MAIN:
            Menu_state = MENU_MAIN;
            Menu_items = MENU_MAIN_ITEMS;
            Menu_strings = Menu_mainStrings;
            break;
        case MENU_SCALE:
            Menu_state = MENU_SCALE;
            Menu_items = MENU_SCALE_ITEMS;
            Menu_strings = Menu_scaleStrings;
            break;
        case MENU_KEY:
            Menu_state = MENU_KEY;
            Menu_items = MENU_KEY_ITEMS;
            Menu_strings = Menu_keyStrings;
            break;
        case MENU_OCTAVE:
            Menu_state = MENU_OCTAVE;
            Menu_items = MENU_OCTAVE_ITEMS;
            Menu_strings = Menu_octaveStrings;
            break;
        case MENU_CHANNEL_SELECT:
            Menu_state = MENU_CHANNEL_SELECT;
            break;

    }
    Menu_redraw(1);
}