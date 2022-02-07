/*
 * Nokia_Driver.h
 *
 *  Created on: Jan 28, 2022
 *      Author: Admin
 */

#ifndef NOKIA_DRIVER_H_
#define NOKIA_DRIVER_H_

extern void SPI_Init();
extern void Switch_LED_Init();
extern void Reset_Init();
extern void LcdCharacter();
extern void LcdString(char *characters);
extern void LcdClear(void);
extern void Position(int x, int y);






#endif /* NOKIA_DRIVER_H_ */
