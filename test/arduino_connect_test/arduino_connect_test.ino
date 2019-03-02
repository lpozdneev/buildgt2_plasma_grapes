void setup() {
    Serial.begin(9600);
    pinMode(11, INPUT);
    //pinMode(7, OUTPUT);
}

void loop()  {
   // Serial.println(analogRead(A3));
    //digitalWrite(7, HIGH);
    Serial.println(digitalRead(11));
    delay(50);
}

//#define ledPin 13
//#define avoidPin 8
//
//void setup()
//{
//pinMode(ledPin, OUTPUT);
//pinMode(avoidPin, INPUT);
//}
//
//void loop()
//{
//  int avoidVal = digitalRead(avoidPin);
//  //digitalWrite(ledPin, LOW);
//  if(avoidVal == LOW) {
//  digitalWrite(ledPin, HIGH);
//  } else {
//  digitalWrite(ledPin, LOW);
//  }
//}
