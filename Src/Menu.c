//
// Created by Wojciech on 12.06.2017.
//
#include <Menu.h>
#include <SSD1306.h>
#include <usbd_midi_if.h>
#include <MIDI_Consts.hpp>

SSD1306_Dev* Menu_display;

#define MENU_MAIN 0
#define MENU_SCALE 1
#define MENU_CHANNEL_SELECT 2

int Menu_state;
int Menu_selectedItem;

#define MENU_MAIN_ITEMS 4
char* Menu_mainStrings[] = {
        "Scales",
        "Modulation",
        "Channels",
        "Params"
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
    Menu_state = MENU_MAIN;
    Menu_redraw();
}

void Menu_left() {
    switch (Menu_state) {
        case MENU_CHANNEL_SELECT:
            MIDI_sendCC(DATA_CHANNEL, CC_NAV_LEFT, CC_VALUE_ON);
            break;

        default:
            break;
    }
}


void Menu_right() {
    switch (Menu_state) {
        case MENU_CHANNEL_SELECT:
            MIDI_sendCC(DATA_CHANNEL, CC_NAV_RIGHT, CC_VALUE_ON);
            break;

        default:
            break;
    }
}


void Menu_ok() {
    switch (Menu_state) {
        case MENU_CHANNEL_SELECT:
            Menu_changeState(MENU_MAIN);
            break;

        default:
            break;
    }
}


void Menu_redraw() {
    SSD1306_clear(Menu_display);
    switch (Menu_state) {
        case MENU_MAIN:
            SSD1306_drawString(Menu_display, 0, 0, "CONTROL MI PMIK", 16);
            SSD1306_drawGlyph(Menu_display, 0, 16, Menu_arrowGlyph);
            for (int i = 0; i < 3; ++i) {
                SSD1306_drawString(Menu_display, 8, 16 * (i + 1), Menu_mainStrings[(i + Menu_selectedItem) % MENU_MAIN_ITEMS], 16);
            }
            break;
        default:
            SSD1306_drawString(Menu_display, 0, 0, "WRONG STATE XD", 16);
            break;
    }

}

void Menu_changeState(int state) {
    switch (state) {
        case MENU_MAIN:
            Menu_state = MENU_MAIN;
            break;
    }
}