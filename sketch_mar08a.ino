#include <Servo.h>

const int analogInPinUD = A0;
const int analogInPinLR = A1;
const int analogOutPin = 5;

Servo myservo1;
//Servo myservo2;
int joyUD;
int joyLR;
int output;
int vInit;
int velocity;
int j;
int aInit;
int accel;


void setup() {
  Serial.begin(9600);
  myservo1.attach(analogOutPin);
  //myservo2.attach(analogOutPin);
  joyUD = 0;
  joyLR = 0;
  output = 0;
  vInit = 0;
  velocity = 0;
  j = 0;
  aInit = 0;
  accel = 0;
}

void loop() {
  velocity = analogRead(analogInPinUD);
  velocity = map(velocity, 0, 1004, -512, 511);
  if(abs(velocity) < 10){
    velocity = 0;
    myservo1.write(output);
  }
  equations();

  Serial.println("*********value***********");
  Serial.println(velocity);

  if(velocity == 0){
    output = 92;
  } else{
    output = map(velocity, -510, 510, 0, 180);
  }
  if(myservo1.read() < output){
    for(int cur = myservo1.read(); cur <= output; cur++){
      myservo1.write(cur);
      delay(15);
    } 
  }  else{
    for(int cur = myservo1.read(); cur >= output; cur--){
      myservo1.write(cur);
      delay(15);
    } 
  }
  if(velocity == 0){
    delay(550);
  }
  /*joystick = analogRead(analogInPinLR);
  output = map(output, 1000, 2000, 0, 180);
  myservo.write(output);
  delay(15);*/
}

void equations(){
  j = (velocity - vInit - aInit * 15)*2/225;
  accel = (velocity - vInit)/15;
  aInit = accel - j * 15;
  velocity = vInit + aInit * 15 + j * 225;
  vInit = velocity;
  
}

