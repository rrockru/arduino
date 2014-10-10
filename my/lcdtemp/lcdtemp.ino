#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

uint8_t char_P[8] = {0x1F,0x11,0x11,0x11,0x11,0x11,0x11};
uint8_t char_D[8] = {0x06,0x0A,0x0A,0x0A,0x0A,0x1F,0x11};
uint8_t char_GRD[8] = {0x06,0x09,0x09,0x06,0x0,0x0,0x0};
LiquidCrystal_I2C    lcd(0x27, 16, 2);

void setup()
{
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.createChar(0, char_P);
  lcd.createChar(1, char_D);
  lcd.createChar(2, char_GRD);
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
    
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    if (!isnan(h) || !isnan(t)) {
      lcd.setCursor(0,1);
      lcd.print("T:");
      lcd.print(t);
      lcd.print("C");
      lcd.write(2);
      lcd.print(", B:");
      lcd.print(h);
      lcd.print("%");
    }
    delay(2000);
  }
  for(int i = 10; i > 0; i--)
  {
    lcd.clear();
    lcd.setCursor(i,0);
    lcd.write(0);
    lcd.print("PEBE");
    lcd.write(1); 
    
    int h = dht.readHumidity();
    int t = dht.readTemperature();
    if (!isnan(h) || !isnan(t)) {
      lcd.setCursor(0,1);
      lcd.print("T:");
      lcd.print(t);
      lcd.print("C");
      lcd.write(2);
      lcd.print(", B:");
      lcd.print(h);
      lcd.print("%");
    }
    delay(2000);
  }  
}
