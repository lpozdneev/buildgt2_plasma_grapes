/*
    Ultrasonic sensor Pins:
        VCC: +5VDC
        Trig : Trigger (INPUT) - Pin11
        Echo: Echo (OUTPUT) - Pin 12
        GND: GND
 */

int avoidPin = 8;

int trigPin1 = 11; // Trigger
int echoPin1 = 12; // Echo
int trigPin2 = 9;
int echoPin2 = 10;
long duration1, cm1, inches;
long duration2, cm2;

int buzzerPin = 3;


void beep(unsigned char delayms) { //creating function
  analogWrite(buzzerPin, 20); //Setting pin to high
  delay(delayms); //Delaying
  analogWrite(buzzerPin ,0); //Setting pin to LOW
  delay(delayms); //Delaying
  
}


void setup()
{
    beep(50);
    //Serial Port begin
    Serial.begin(9600);
    //Define inputs and outputs
    pinMode(trigPin1, OUTPUT);
    pinMode(echoPin1, INPUT);
    pinMode(trigPin2, OUTPUT);
    pinMode(echoPin2, INPUT);
}

void loop()
{


    // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
    // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
    digitalWrite(trigPin1, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin1, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin1, LOW);
    
    //digitalWrite(trigPin2, LOW);
    //delayMicroseconds(5);
    //digitalWrite(trigPin2, HIGH);
    //delayMicroseconds(10);
    //digitalWrite(trigPin2, LOW);
    // Read the signal from the sensor: a HIGH pulse whose
    // duration is the time (in microseconds) from the sending
    // of the ping to the reception of its echo off of an object.
    pinMode(echoPin1, INPUT);
    duration1 = pulseIn(echoPin1, HIGH);
    //pinMode(echoPin2, INPUT);
    //duration2 = pulseIn(echoPin2, HIGH);


    // Convert the time into a distance
    cm1 = (duration1 / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343
    //inches = (duration / 2) / 74; // Divide by 74 or multiply by 0.0135

    delayMicroseconds(50);

    digitalWrite(trigPin2, LOW);
    delayMicroseconds(5);
    digitalWrite(trigPin2, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin2, LOW);
    pinMode(echoPin2, INPUT);
    duration2 = pulseIn(echoPin2, HIGH);  
    cm2 = (duration2 / 2) / 29.1;   // Divide by 29.1 or multiply by 0.0343

    //Serial.print(inches);
    //Serial.print("in, ");
//    Serial.print(cm1);
//    Serial.print("cm1 ");
//    Serial.print(cm2);
//    Serial.print("cm2");
//    Serial.println();

    Serial.print(min(cm1, cm2));

    delay(50);
}
