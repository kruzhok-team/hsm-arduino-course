#include <Wire.h>
#include "LCD_I2C.h"

#define LCD_DEVICE       0x27
#define LCD_ROWS         2
#define LCD_COLUMNS      16

LCD_I2C lcd(LCD_DEVICE, LCD_COLUMNS, LCD_ROWS);

int time;

void setup()
{
    lcd.begin();
    lcd.backlight();
    lcd.clear();
    lcd.print("Hello, World!");
    delay(1000);
    time = 0;
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Time: ");
}

void loop()
{
    char buffer[6];
    int minutes = time / 60;
    int seconds = time % 60;
    snprintf(buffer, 6, "%02d:%02d", minutes, seconds);
    
    lcd.setCursor(6, 0);
    lcd.print(buffer);
    
    time++;
    delay(1000);
}
