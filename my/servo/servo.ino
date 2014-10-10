#include <Servo.h>

#define SW_PIN    2
#define X_PIN     A0
#define Y_PIN     A1

Servo myservo;

void setup()
{
  myservo.attach(9);
  pinMode(SW_PIN, INPUT);
  digitalWrite(SW_PIN, HIGH);
  Serial.begin(115200);
}

void loop()
{
  /*
  Serial.print(digitalRead(SW_PIN));
  Serial.print(" @ ");
  Serial.print(analogRead(X_PIN));
  Serial.print("x");
  */
  int y = analogRead(Y_PIN);
  //Serial.println(y);
  //myservo.write(y/5);
  String inString;
  while (Serial.available() > 0) {
    int inChar = Serial.read();
    inString += (char)inChar; 
  }
  if (inString != "")
  {
    if (inString == "left")
      myservo.write(180);
    else if (inString == "right")
      myservo.write(13);
    else if (inString == "top")
      myservo.write(90);
  }
  /*if (v >= 0 && v <= 180)
  {
    myservo.write(v);
    Serial.write("Angle: ");
    Serial.println(v);
  }*/
  delay(10);
}
