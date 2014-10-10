#include <Servo.h>

#define SW_PIN    2
#define X_PIN     A0
#define Y_PIN     A1

Servo myservo;

void setup()
{
  myservo.attach(9, 680, 2400);
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);
}

void loop()
{
  int y = analogRead(Y_PIN);
  myservo.write(y/5);
  delay(10);
}
