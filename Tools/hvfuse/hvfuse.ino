/*  
 HVFuse - Use High Voltage Programming Mode to Set Fuses on ATmega48/88/168
 09/23/08  Jeff Keyzer  http://mightyohm.com                
 The HV programming routines are based on those described in the
 ATmega48/88/168 datasheet 2545M-AVR-09/07, pg. 290-297
 This program should work for other members of the AVR family, but has only
 been verified to work with the ATmega168.  If it works for you, please
 let me know!  http://mightyohm.com/blog/contact/
 */

// Desired fuse configuration
#define  HFUSE  0xDF   // Default for ATmega48/88/168, for others see
#define  LFUSE  0x62   // http://www.engbedded.com/cgi-bin/fc.cgi

// Pin Assignments
#define  DATA    PORTD // PORTD = Arduino Digital pins 0-7
#define  DATAD   DDRD  // Data direction register for DATA port
#define  VCC     8
#define  RDY     12     // RDY/!BSY signal from target
#define  OE      11
#define  WR      10
#define  BS1     9
#define  XA0     13
#define  XA1     18    // Analog inputs 0-5 can be addressed as
#define  PAGEL   19    // digital outputs 14-19
#define  RST     14    // Output to level shifter for !RESET
#define  BS2     16
#define  XTAL1   17

#define  BUTTON  15    // Run button

void setup()  // run once, when the sketch starts
{
  
  Serial.begin(19200);
  // Set up control lines for HV parallel programming
  DATA = 0x00;  // Clear digital pins 0-7
  DATAD = 0xFF; // set digital pins 0-7 as outputs
  pinMode(VCC, OUTPUT);
  pinMode(RDY, INPUT);
  pinMode(OE, OUTPUT);
  pinMode(WR, OUTPUT);
  pinMode(BS1, OUTPUT);
  pinMode(XA0, OUTPUT);
  pinMode(XA1, OUTPUT);
  pinMode(PAGEL, OUTPUT);
  pinMode(RST, OUTPUT);  // signal to level shifter for +12V !RESET
  pinMode(BS2, OUTPUT);
  pinMode(XTAL1, OUTPUT);

  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);  // turn on pullup resistor

  // Initialize output pins as needed
  digitalWrite(RST, HIGH);  // Level shifter is inverting, this shuts off 12V
  
  Serial.println("Ready.");
}

void loop()  // run over and over again
{
  while(digitalRead(BUTTON) == HIGH) {  // wait until button is pressed
  }
  // Initialize pins to enter programming mode
  Serial.println("Initialize pins to enter programming mode");
  digitalWrite(PAGEL, LOW);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
  // Enter programming mode
  Serial.println("Enter programming mode");
  digitalWrite(VCC, HIGH);  // Apply VCC to start programming process
  digitalWrite(WR, HIGH);  // Now we can assert !OE and !WR
  digitalWrite(OE, HIGH);
  delay(1);
  digitalWrite(RST, LOW);   // Apply 12V to !RESET thru level shifter
  delay(1);
  // Now we're in programming mode until RST is set HIGH again
  
  // First we program HFUSE
  Serial.print("Programming HFUSE");
  sendcmd(B01000000);  // Send command to enable fuse programming mode
  writefuse(HFUSE, true);

  // Now we program LFUSE
  Serial.print("Programming LFUSE");
  sendcmd(B01000000);
  writefuse(LFUSE, false);
  
  //Serial.print("Erase chip");
  //sendcmd(B10000000);
  //erase();
  
  Serial.println("Reading fuses:");
  sendcmd(B00000100);
  readlfuse();
  //sendcmd(B00000100);
  readhfuse();
  //sendcmd(B00000100);
  readefuse();
  
  Serial.println("Reading signature:");
  sendcmd(B00001000);
  readsign();  

  Serial.println("Waiting 1s");
  delay(5000);  // wait a while to allow button to be released

  // Exit programming mode
  Serial.println("Exit programming mode");
  digitalWrite(RST, HIGH);

  // Turn off all outputs
  Serial.println("Turn off all pins");
  DATA = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(WR, LOW);
  digitalWrite(PAGEL, LOW);
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(BS2, LOW);
  digitalWrite(VCC, LOW);
  
  Serial.println("Done!");
}

void sendcmd(byte command)  // Send command to target AVR
{
  // Set controls for command mode
  digitalWrite(XA1, HIGH);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  //DATA = B01000000;  // Command to load fuse bits
  DATA = command;
  digitalWrite(XTAL1, HIGH);  // pulse XTAL to send command to target
  delay(1);
  digitalWrite(XTAL1, LOW);
  //delay(1);
}

void writefuse(byte fuse, boolean highbyte)  // write high or low fuse to AVR
{
  // if highbyte = true, then we program HFUSE, otherwise LFUSE
  
  // Enable data loading
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, HIGH);
  delay(1);
  // Write fuse
  DATA = fuse;  // set desired fuse value
  digitalWrite(XTAL1, HIGH);
  delay(1);
  digitalWrite(XTAL1, LOW);
  if(highbyte == true)
    digitalWrite(BS1, HIGH);  // program HFUSE
  else
    digitalWrite(BS1, LOW);
  digitalWrite(WR, LOW);
  delay(1);
  digitalWrite(WR, HIGH);
  while(digitalRead(RDY) == LOW)
  {
    Serial.print(".");
  }
  Serial.println(".");
  delay(100);
}

void erase()
{
  digitalWrite(WR, LOW);
  delay(1);
  digitalWrite(WR, HIGH);
  while(digitalRead(RDY) == LOW)
  {
    Serial.print(".");
    delay(1000);
  }
  Serial.println(".");
  delay(100);
}

void readlfuse()
{
  DATAD = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(BS2, LOW);
  digitalWrite(BS1, LOW);
  byte lfuse = DATA;
  Serial.print("LFUSE: ");
  Serial.println(lfuse, HEX);
  //DATAD = 0xFF;
  //digitalWrite(OE, HIGH);
}

void readhfuse()
{
  //DATAD = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(BS2, HIGH);
  digitalWrite(BS1, HIGH);
  byte hfuse = DATA;
  Serial.print("HFUSE: ");
  Serial.println(hfuse, HEX);
  //DATAD = 0xFF;
  //digitalWrite(OE, HIGH);
}

void readefuse()
{
  //DATAD = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(BS2, HIGH);
  digitalWrite(BS1, LOW);
  byte efuse = DATA;
  Serial.print("EFUSE: ");
  Serial.println(efuse, HEX);
  DATAD = 0xFF;
  digitalWrite(OE, HIGH);
}

void readsign()
{
  digitalWrite(XA1, LOW);
  digitalWrite(XA0, LOW);
  digitalWrite(BS1, LOW);
  DATA = 0x01;
  digitalWrite(XTAL1, HIGH);  // pulse XTAL to send command to target
  delay(1);
  digitalWrite(XTAL1, LOW);
  DATAD = 0x00;
  digitalWrite(OE, LOW);
  digitalWrite(BS1, LOW);
  digitalWrite(XTAL1, HIGH);  // pulse XTAL to send command to target
  delay(1);
  digitalWrite(XTAL1, LOW);
  byte sign = DATA;
  Serial.print("SIGN: ");
  Serial.println(sign, HEX);
  DATAD = 0xFF;
  digitalWrite(OE, HIGH);
}
