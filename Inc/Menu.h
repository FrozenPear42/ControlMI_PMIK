#ifndef CONTROLMI_PMIK_MENU_H
#define CONTROLMI_PMIK_MENU_H

#include <SSD1306.h>

void Menu_init(SSD1306_Dev* display);

void Menu_show();

void Menu_left();

void Menu_right();

void Menu_ok();

void Menu_redraw();

void Menu_changeState(int state);

#endif //CONTROLMI_PMIK_MENU_H
