#include <IRremote.h>

#define RECV_PIN 2
#define LED_PIN 3

IRrecv irrecv(RECV_PIN);

decode_results results;

int state = 0;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(LED_PIN, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    if (results.value == 0xF4BA2988)
    {
      state = !state;
      digitalWrite(LED_PIN, state?LOW:HIGH);
    }
    irrecv.resume(); // Receive the next value
  }
}
