/*
 * LCD.h
 *
 *  Created on: Apr 18, 2022
 *      Author: Kushal Nesarkar
 */

#ifndef LCD_H_
#define LCD_H_

   void LCD_Command(uint8_t c);
   void LCD_init(void);
   void Display_character(unsigned char d);
   void Display_string(unsigned char *d);
   void LCD_Clear(void);
   void LCD_cursorPosition(uint8_t line);



#endif /* LCD_H_ */
