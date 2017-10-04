
// - CE to Arduino pin 9

// - CSN to Arduino pin 10
// NRF before setup code
#include <SPI.h>   // Comes with Arduino IDE
#include "RF24.h"  // Download and Install (See above)
#include <Servo.h>
Servo myservo;  // create servo object to control a servo
RF24 myRadio (9, 10); // "myRadio" is the identifier you will use in following methods
byte addresses[][6] = {"1Node"}; // Create address for 1 pipe.
int dataReceived;  // Data that will be received from the transmitter
// End Nrf before setup code

int pos = 0;    // variable to store the servo position
int buttonInput = 4;  // set the button input to pin 4
int buttonState = 0;  // create an int called buttonState
int reset = 0;     // create an int to help with reset


void setup() {
  // Use the serial Monitor (Symbol on far right). Set speed to 115200 (Bottom Right)
  Serial.begin(115200);
  delay(1000);
  Serial.println(F("RF24/Simple Receive data Test"));
  Serial.println(F("Questions: terry@yourduino.com"));

  myRadio.begin();  // Start up the physical nRF24L01 Radio
  myRadio.setChannel(108);  // Above most Wifi Channels
  // Set the PA Level low to prevent power supply related issues since this is a
  // getting_started sketch, and the likelihood of close proximity of the devices. RF24_PA_MAX is default.
  myRadio.setPALevel(RF24_PA_MIN);
  //  myRadio.setPALevel(RF24_PA_MAX);  // Uncomment for more power

  myRadio.openReadingPipe(1, addresses[0]); // Use the first entry in array 'addresses' (Only 1 right now)
  myRadio.startListening();

  myservo.attach(3);  // attaches the servo on pin 9 to the servo object
  pinMode(buttonInput, INPUT); // sets the button input as INPUT
  digitalWrite(buttonInput, HIGH); //sets the buttoninput of a button to HIGH
    

}




void loop() {
    // put your main code here, to run repeatedly:
    
    if ( myRadio.available()) // Check for incoming data from transmitter
    {
      //for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
          //in steps of 1 degree
          //myservo.write(pos);              // tell servo to go to position in variable 'pos'
          //delay(20);                       // waits 20ms for the servo to reach the position
          //if(pos == 0){
            //reset = 1;
          //}
      resetservo();
      }
      while(myRadio.available())  // While there is data ready
      {
        myRadio.read( &dataReceived, sizeof(dataReceived) ); // Get the data payload (You must have defined that already!)
      
        // DO something with the data, like print it
        Serial.print("Data received = ");
        Serial.println(dataReceived);
        if(dataReceived){       // checks if the button has been pressed
            Serial.println("Communicated with the servo");
            //myservo.write(180);          // rotates the servo 180 degrees
            moveservo();
            dataReceived = 0;
            //reset = 0;
              }
           }
         }
      //}

void resetservo(){
    for (pos = 180; pos >= 0; pos -= 1) { // goes from 180 degrees to 0 degrees
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(30);                       // waits 15ms for the servo to reach the position
  }
}

void moveservo(){
    for (pos = 0; pos <= 180; pos += 1) { // goes from 0 degrees to 180 degrees
    // in steps of 1 degree
    myservo.write(pos);              // tell servo to go to position in variable 'pos'
    delay(20);                       // waits 15ms for the servo to reach the position
  }
}

