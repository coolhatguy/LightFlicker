
#include <Servo.h>
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // includes the RF24 library


Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards
// - CE to Arduino pin 9
// - CSN to Arduino pin 10
RF24 myRadio (9, 10); // "myRadio" is the identifier used in following methods

byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
int dataTransmitted;  // Data that will be Transmitted from the transmitter


int pos = 0;    // variable to store the servo position
int buttonInput = 4;  // set the button input to pin 4
int buttonState = 0;  // create an int called buttonState

void setup() {
  // NRF Setupcode
  // Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("RF24/Simple Transmit data Test"));
  Serial.println(F("Questions: terry@yourduino.com"));
  dataTransmitted = 100; // Arbitrary known data to transmit. Change it to test...
  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MIN);
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power
  myRadio.openWritingPipe( addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  delay(1000);
  // End NRF Setupcode



  

  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonInput, INPUT_PULLUP); // sets the button input as INPUT
    
}

void loop() {


  //NRF Test code


  buttonState = digitalRead(buttonInput);   //sets the button state to the read of the buttoninput
  
  // put your main code here, to run repeatedly:

  if(buttonState == LOW){       // checks if the button has been pressed
      myRadio.write( &dataTransmitted, sizeof(dataTransmitted) ); //  Transmit the data
      Serial.print(F("Data Transmitted = "));
      Serial.print(dataTransmitted);
      Serial.println(F(" No Acknowledge expected"));
      dataTransmitted = dataTransmitted + 1;  // Send different data next time
      delay(500);
      //end NRF Test Code
   }
}
