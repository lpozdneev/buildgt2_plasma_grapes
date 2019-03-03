#include <Servo.h>



int chestTriggerPin = 6;
int chestEchoPin =12;


int headTriggerPin = 10;
int headEchoPin = 13;

int leftBuzzer = 11;
int rightBuzzer = 3;

int buzzerPin = 9;

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
#define NUM_ANGLES 7
unsigned char sensorAngle[NUM_ANGLES] = {60,70,80,90,100,110,120};
unsigned int distance [NUM_ANGLES];
//unsigned char angleIndex = 0;


void readNextDistance() {
  static unsigned char angleIndex = 0;
  static signed char step = 1;

  distance[angleIndex] = getCM(11,12);
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
  if (myServo.read() > 90) {
    buzzPin = rightBuzzer;
  } else if (myServo.read() < 90) {
    buzzPin = leftBuzzer;
  }
  if (buzzPin != 0) {
    tone(buzzPin, 1000 - (5 * dist));
    delay(100);
    noTone(buzzPin);
  } else {
    tone(rightBuzzer, 1000 - (5 * dist));
    delay(100);
    noTone(buzzPin);
    tone(leftBuzzer, 1000 - (5 * dist));
    delay(100);
    noTone(buzzPin);
  }
  
}

void sweep() {
  //myServo.write(sensorAngle[0]);
  //myServo.write(90);
  //delay(1500);
     for (unsigned char i = 0; i < NUM_ANGLES; i++) {
    readNextDistance(), delay(500);
    Serial.print(distance[i]);
    Serial.print(" | ");
    //beep(20, distance[i]);
    if (distance[i] < 100) {
      //advancedBuzz(distance[i]);
    }
  }
  Serial.println();
  //delay(1500);
}

void headBuzz() {
  int headDist = getCM(chestTriggerPin, chestEchoPin);
  if (headDist > 100) {
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

  /*
   myServo.write(90);
   myServo.write(sensorAngle[0]);
   delay(600);
   for (unsigned char i = 0; i < NUM_ANGLES; i++) {
    readNextDistance(), delay(200);
    //beep(20, distance[i]);
    if (distance[i] < 100) {
      beep(20, distance[i]);
    }
    Serial.print(distance[i]);
    Serial.print(" | ");
   }
    */
    


    
    pinMode(leftBuzzer, OUTPUT);
    pinMode(rightBuzzer, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
    tone(rightBuzzer,440);
    delay(1000);
    noTone(rightBuzzer);
    tone(leftBuzzer,440   );
    delay(1000);
    noTone(leftBuzzer);

    pinMode(conditionalPin, INPUT);
    sweep();
}

void loop() {
  // put your main code here, to run repeatedly:
  //Serial.print(getCM(chestTriggerPin,chestEchoPin));
  //Serial.print(" ||| ");
  //Serial.print(getCM(headTriggerPin, headEchoPin));
  //Serial.println();
  //sweep();
  if (digitalRead(conditionalPin) == HIGH) {
    sweep();
    headBuzz();
  }  
  //headBuzz();
  //delay(250);
}
