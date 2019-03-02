
#include <Servo.h>



int chestTriggerPin = 11;
int chestEchoPin =12;


int headTriggerPin = 9;
int headEchoPin = 10;


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

void fillDistanceArray(int *distanceArray, int triggerPin, int echoPin, Servo *theServo) {
  int pos = 0;
  theServo.write(pos);
  delay(15);
  for (int i = 0; i < 10; i++) {
    pos += 18
    theServo.write(pos);
    distanceArray[i] = getCM(triggerPin, echoPin);
    delay(15)
  }
}




void setup() {
   Serial.begin(9600);
   pinMode(chestTriggerPin, OUTPUT);
   pinMode(chestEchoPin, INPUT);
   pinMode(headTriggerPin,OUTPUT);
   pinMode(headEchoPin,INPUT);

   myServo.attach(servoPin);

   //one sweep of servo
   fillDistanceArray(&distanceArray, triggerPin, echoPin, &myServo);
   for (int i = 0; i < 10; i++) {
    Serial.print(" | ");
    Serial.print(distanceArray[i]);
   }
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.print(getCM(chestTriggerPin,chestEchoPin));
  Serial.print(" | ");
  Serial.print(getCM(headTriggerPin, headEchoPin));

  delay(250);
}
