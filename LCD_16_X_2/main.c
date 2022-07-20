/*                      LCD Commands:
 * |    Hex    |   Command to LCD Instruction Register  |
 * ------------------------------------------------------
 *      0X0F        LCD ON , Cursor ON
 *      0x01        Clear Screen
 *      0x02        Return Home
 *      0x04        Shift Cursor to Left
 *      0x05        Shift Display right
 *      0x06        Shift Cursor to Right
 *      0x07        Shift Display left
 *      0x0E        Display On Cursor Blinking
 *      0X80        Force Cursor to Beginning of First line
 *      0XC0        Force Cursor to Beginning of Second line
 *      0X38        2 lines and 5×7 matrix
 *      0X83        Cursor line 1 position 3
 *      0x3C        Activate second line
 *      0X08        Display OFF, cursor OFF
 *      0XC1        Jump to second line, position 1
 *      0X0C        Display ON, cursor OFF
 *      0XC1        Jump to second line, position 1
 *      0XC2        Jump to second line, position 2
 *
 */


/* 4 Bit LCD 16x2 Connection

  1=VSS  =GND
  2=VCC  =+5V
  3=POT  =Signal pin,(One pin of POT to +5V , One pin of POT to GND)
  4=Reg  =PD0
  5=r/w  =PD1
  6=En   =PD2
  7=D0   =NC(No connection)
  8=D1   =NC(No connection)
  9=D2   =NC(No connection)
  10=D3  =NC(No connection)
  11=D4  =PA4
  12=D5  =PA5
  13=D6  =PA6
  14=D7  =PA7
  15=+LED=+5V
  16=-LED=GND

*/

#include <stdint.h>
#include <stdbool.h>
#include "inc/tm4c123gh6pm.h"
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/gpio.h"

int main()
{
    int i=0,strlen;
    SysCtlClockSet(SYSCTL_SYSDIV_5|SYSCTL_XTAL_16MHZ|SYSCTL_USE_PLL | SYSCTL_OSC_MAIN);

    LCD_init();
    LCD_Clear(); // Clear the Screen
    SysCtlDelay(13333333);
    LCD_Command(0x0E); //Display ON, Cursor blinking
    SysCtlDelay(13333333);
    LCD_Clear(); // Clear the Screen
    SysCtlDelay(13333333);
    LCD_cursorPosition(2,5);// Cursor position
    SysCtlDelay(13333333);
    Display_string("India "); // Display Data
    SysCtlDelay(13333333);


    while(1)
    {

    }

    }
