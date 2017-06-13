#ifndef CONTROLMI_PMIK_MENU_H
#define CONTROLMI_PMIK_MENU_H

/*!
 * @file
 *
 * @brief Functions responsible for displaying current status at the SSD1306 display.
 *
 */

#include <SSD1306.h>

/*!
 * @brief Initializes the menu on the display.
 * @param display pointer to the displays driver.
 */
void Menu_init(SSD1306_Dev* display);


/*!
 * @brief Function processes input from the encoder.
 * @param value encoder's value
 */
void Menu_processEncoder(uint32_t value);


/*!
 * @brief Function is called when encoder rotated to left.
 */
void Menu_left();

/*!
 * @brief Function is called when encoder rotated to right.
 */
void Menu_right();

/*!
 * @brief Function is called when clicked confirmation button.
 */
void Menu_ok();

/*!
 * @brief Updates and redraws display's content.
 * @param force
 */
void Menu_redraw(uint8_t force);

/*!
 * @brief Function deals with menu states and connections between them.
 * @param state
 */
void Menu_changeState(int state);

extern uint8_t Menu_selectedScale;
extern uint8_t Menu_selectedKey;
extern uint8_t Menu_selectedOctave;
extern uint8_t Menu_velocity;


#endif //CONTROLMI_PMIK_MENU_H
