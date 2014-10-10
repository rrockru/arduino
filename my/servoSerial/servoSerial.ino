#include <Servo.h>

Servo myservo;

void setup()
{
  myservo.attach(9);
  Serial.begin(115200);
  Serial.println("Type left, right or top");
}

void loop()
{
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
      
    Serial.print("Turned ");
    Serial.println(inString);
  }
  delay(10);
}
