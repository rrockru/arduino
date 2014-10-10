#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <DHT.h>

#define DHTPIN 2 
#define DHTTYPE DHT11
DHT dht(DHTPIN, DHTTYPE);

uint8_t char_GRD[8] = {0x06,0x09,0x09,0x06,0x0,0x0,0x0};
LiquidCrystal_I2C    lcd(0x27, 16, 2);

void setup()
{
  dht.begin();
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  
  lcd.createChar(0, char_GRD);
  lcd.home();
}

void loop()
{
  int h = dht.readHumidity();
  int t = dht.readTemperature();
  if (!isnan(h) || !isnan(t)) {
    lcd.setCursor(0,1);
    lcd.print("T:");
    lcd.print(t);
    lcd.print("C");
    lcd.write(0);
    lcd.print(", B:");
    lcd.print(h);
    lcd.print("%");
  }
  delay(2000);
}
