#ifndef CONTROLMI_PMIK_MENU_H
#define CONTROLMI_PMIK_MENU_H

#include <SSD1306.h>

void Menu_init(SSD1306_Dev* display);

void Menu_processEncoder(uint32_t value);

void Menu_show();

void Menu_left();

void Menu_right();

void Menu_ok();

void Menu_redraw(uint8_t force);

void Menu_changeState(int state);

extern uint8_t Menu_selectedScale;
extern uint8_t Menu_selectedKey;
extern uint8_t Menu_selectedOctave;
extern uint8_t Menu_velocity;


#endif //CONTROLMI_PMIK_MENU_H
