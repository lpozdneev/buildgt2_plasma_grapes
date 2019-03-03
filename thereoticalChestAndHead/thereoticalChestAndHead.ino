#include <Servo.h>


boolean toBuzzOrNot = true;

int chestTriggerPin = 6;
int chestEchoPin =12;


int headTriggerPin = 10;
int headEchoPin = 2;

int leftBuzzer = 11;
int rightBuzzer = 9;

int buzzerPin = 3;//9

int conditionalPin = 4;


int getCM (int trigPin, int echoPin) {
     digitalWrite(trigPin, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    pinMode(echoPin,INPUT);
    return (pulseIn(echoPin, HIGH) / 2) / 29.1;
}


//Servo stuff
Servo myServo;
int servoPos = 0;
int servoPin = 5; //needs to be PWM pin
int distanceArray[10];


//from colubia tutorial
#define NUM_ANGLES 3//7
//unsigned char sensorAngle[NUM_ANGLES] = {60,70,80,90,100,110,120};
unsigned char sensorAngle[NUM_ANGLES] = {45,85,125};
unsigned int distance [NUM_ANGLES];
//unsigned char angleIndex = 0;


void readNextDistance() {
  static unsigned char angleIndex = 0;
  static signed char step = 1;

  distance[angleIndex] = getCM(chestTriggerPin,chestEchoPin);
  angleIndex += step;
  if (angleIndex == NUM_ANGLES - 1) step = -1;
  else if (angleIndex == 0) step = 1;
  myServo.write(sensorAngle[angleIndex]);
}


void beep(unsigned char delayms, int pitch) { //creating function
  int finalPitch = pitch;
  if (finalPitch > 1000) {
    finalPitch = 1000;
  }
  finalPitch = 1000 - finalPitch;
  finalPitch = finalPitch*1000;
  analogWrite(buzzerPin, finalPitch); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  
}

void advancedBuzz(int dist) {
  int buzzPin = 0;
  if (myServo.read() > 90 && toBuzzOrNot) {
    buzzPin = leftBuzzer;
    toBuzzOrNot = false;
    Serial.print("---right: ");
    Serial.print(myServo.read());
  } else if (myServo.read() < 80) {
    buzzPin = rightBuzzer;
    toBuzzOrNot = false;
    Serial.print("---left: ");
    Serial.print(myServo.read());
  }
  tone(buzzPin,1000 - ( 5 * dist));
  delay(100);
  noTone(buzzPin);
  
//  if (buzzPin != 0) {
//    tone(buzzPin, 1000 - (5 * dist));
//    delay(100);
//    noTone(buzzPin);
//  } //else {
//    //tone(rightBuzzer, 1000 - (5 * dist));
//    
//    delay(100);
//    noTone(rightBuzzer);
//    tone(leftBuzzer, 1000 - (5 * dist));
//    delay(100);
//    noTone(leftBuzzer);
  //}
  noTone(leftBuzzer);
  noTone(rightBuzzer);
  
}

/*
void sweep() {
  //myServo.write(sensorAngle[0]);
  //myServo.write(90);
  //delay(1500);
     for (unsigned char i = 0; i < NUM_ANGLES; i++) {
    readNextDistance(), delay(150);
    headBuzz();
    toBuzzOrNot = true;
    Serial.print(distance[i]);
    Serial.print(" | ");
    //beep(20, distance[i]);
    if (distance[i] < 60) {
      Serial.print("sweep buzz");
      Serial.print(distance[i]);
      advancedBuzz(distance[i]);
    }
  }
  Serial.println();
  //delay(1500);
} */

void sweep() {
  for (unsigned char i = 0; i < NUM_ANGLES; i++) 
  {
    delay(150);
    headBuzz();
    toBuzzOrNot = true;
    int dist = getCM(chestTriggerPin, chestEchoPin);
    Serial.print(dist);
    Serial.print(" | ");
    //beep(20, distance[i]);
    if (dist < 60) {
      Serial.print("sweep buzz");
      Serial.print(dist);
      advancedBuzz(dist);
    }
    myServo.write(sensorAngle[i]);
  }
  Serial.println();
}

void headBuzz() {
  int headDist = getCM(headTriggerPin, headEchoPin);
  //Serial.print(headDist);
  //Serial.println();
  if (headDist < 60) {
    beep(20, headDist);
  }
  
}

void setup() {
   Serial.begin(9600);
   pinMode(chestTriggerPin, OUTPUT);
   pinMode(chestEchoPin, INPUT);
   pinMode(headTriggerPin,OUTPUT);
   pinMode(headEchoPin,INPUT);

   myServo.attach(servoPin);
    
    pinMode(leftBuzzer, OUTPUT);
    pinMode(rightBuzzer, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    
    tone(rightBuzzer,440);
    delay(1000);
    noTone(rightBuzzer);
    tone(leftBuzzer,440   );
    delay(1000);
    noTone(leftBuzzer); 
    

    analogWrite(buzzerPin, 261);
    delay(500);
    analogWrite(buzzerPin,0);
    
    myServo.write(0);
    pinMode(conditionalPin, INPUT);
    sweep();
}

void loop() {
  //sweep();
//  if (digitalRead(conditionalPin) == HIGH) {
  sweep();
  //headBuzz();
  
}
