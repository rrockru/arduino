#include <Wire.h>
#include <LiquidCrystal_I2C.h>

uint8_t char_P[8] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x11};
uint8_t char_D[8] = {0x06,0x0A,0x0A,0x0A,0x0A,0x1F,0x11};
LiquidCrystal_I2C    lcd(0x27, 16, 2);

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.createChar(0, char_P);
  lcd.createChar(1, char_D);
  lcd.home();
}

void loop()
{
  for(int i = 0; i <= 9; i++)
  {
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.write(0);
    lcd.print("PEBE");
    lcd.write(1); 
    delay(500);
  }
  for(int i = 10; i > 0; i--)
  {
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.write(0);
    lcd.print("PEBE");
    lcd.write(1); 
    delay(500);
  }  
}
