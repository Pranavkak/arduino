#include <SPI.h>  
#include "RF24.h" 

RF24 myRadio (7, 8); 

byte addresses[][6] = {"0"}; 

// Setup the servos
Servo leftServo;
Servo rightServo;

void setup() 
{
  Serial.begin(115200);
  delay(1000);

  leftServo.attach(9);
  rightServo.attach(10);

  myRadio.begin(); 
  myRadio.setChannel(115); 
  myRadio.setPALevel(RF24_PA_MAX);
  myRadio.setDataRate( RF24_250KBPS ) ; 
  myRadio.openReadingPipe(1, addresses[0]);
  myRadio.startListening();
}


void loop()  
{

  if ( myRadio.available()) 
  {
    while (myRadio.available())
    {
      char message;
      myRadio.read(&message, sizeof(char));
    }
    switch (message) {
      case 'm':
        moveForward();
        break;
      case 'r':
        turnRight();
        break;
      case 'l':
        turnLeft();
        break;
    }
  }

}

void moveForward() {
  leftServo.write(90); //adjust the angles based on setup
  rightServo.write(90); 
}

void turnRight() {
  leftServo.write(0); 
  rightServo.write(180); 
}

void turnLeft() {
  leftServo.write(180); 
  rightServo.write(0); 
}