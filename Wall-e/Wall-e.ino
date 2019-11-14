#include <Servo.h>
#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(7,8);
const byte address[6] = "00001";
Servo left;
Servo right;
int joy[2]={90,90};

void setup() {  
  left.attach(3);
  right.attach(10);
  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address);
  radio.setPALevel(RF24_PA_MIN);
  radio.startListening();
}
void loop() {
  if(radio.available()){
    radio.read(&joy, sizeof(joy));
    int x = map(joy[0]-joy[1],-512,512,0,180);
    int y = map(joy[0]+joy[1],512,1536,180,0);
    right.write(x<=100&&x>=85?90:x);
    left.write(y<=100&&y>=85?90:y);
  }
}
