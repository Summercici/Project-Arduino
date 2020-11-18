#include <Servo.h>                      // Include servo library

Servo servoLeft;                        // Declare left and right servos

Servo servoRight;

const int trigPinF = 9;
const int echoPinF = 10;
long durationF;
int distF;

const int trigPinL = 3;
const int echoPinL = 4;
long durationL;
int distL;

const int trigPinR = 5;
const int echoPinR = 6;
long durationR;
int distR;

void setup()                            // Built-in initialization block
{   
    Serial.begin(9600);
    pinMode(trigPinF, OUTPUT);
    pinMode(echoPinF, INPUT);
    pinMode(trigPinL, OUTPUT);
    pinMode(echoPinL, INPUT);
    pinMode(trigPinR, OUTPUT);
    pinMode(echoPinR, INPUT);
    servoLeft.attach(13);               // Attach left signal to pin 13
    servoRight.attach(12);              // Attach right signal to pin 12
}

void loop()                             // Main loop auto-repeats
{
  //forward();
//  Serial.println(frontDist());
//  Serial.println(leftDist());
//  Serial.println(rightDist());
//  delay(2000);
  if (frontDist() > 7){
    adjust();//
    forward();
  }

  else if(frontDist() <= 8){
    
    
    if(leftDist() >= 10){ //左边没东西
    turnLeft();
    //forward();
    }

    else if(leftDist() < 10 && rightDist() >=10){ //左边有东西
      turnRight();
      //forward();
    }

    else{
      servoLeft.writeMicroseconds(1500);
      servoRight.writeMicroseconds(1500); // 左转
      delay(650);

      Serial.println("Collect the ball");
      //手动调头
    }

  }
}

int frontDist(){
  digitalWrite(trigPinF, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinF, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinF, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationF = pulseIn(echoPinF, HIGH);
  // Calculating the distance
  distF = durationF*0.034/2;
  return distF;
}

int leftDist(){
  digitalWrite(trigPinL, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinL, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinL, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationL = pulseIn(echoPinL, HIGH);
  // Calculating the distance
  int distance = durationL*0.034/2;
  return distance;
}

int rightDist(){
  digitalWrite(trigPinR, LOW);
  delayMicroseconds(2);
  // Sets the trigPin on HIGH state for 10 micro seconds
  digitalWrite(trigPinR, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPinR, LOW);
  // Reads the echoPin, returns the sound wave travel time in microseconds
  durationR = pulseIn(echoPinR, HIGH);
  // Calculating the distance
  int distance = durationR*0.034/2;
  return distance;
}

void adjust(){
  if (leftDist() < 3){
    servoLeft.writeMicroseconds(1700);
    servoRight.writeMicroseconds(1700);
    delay(75);
  }

  else if(rightDist() < 3){
    servoLeft.writeMicroseconds(1300);
    servoRight.writeMicroseconds(1300);
    delay(75);
  }
}

void forward(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1300);
  delay(100);
}

void turnLeft(){
  servoLeft.writeMicroseconds(1300);
  servoRight.writeMicroseconds(1300);
  delay(575);
}

void turnRight(){
  servoLeft.writeMicroseconds(1700);
  servoRight.writeMicroseconds(1700);
  delay(575);
}
