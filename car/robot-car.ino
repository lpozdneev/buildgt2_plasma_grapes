
// Ultrasonic Module pins
const int linePinLeft = 12;
const int linePinRight = 11;

// Motor control pins : L298N H bridge
const int enAPin = 6; // Left motor PWM speed control
const int in1Pin = 7; // Left motor Direction 1
const int in2Pin = 5; // Left motor Direction 2
const int in3Pin = 4; // Right motor Direction 1
const int in4Pin = 2; // Right motor Direction 2
const int enBPin = 3; // Right motor PWM speed control

bool testDrive = true;

enum Motor
{
    LEFT,
    RIGHT
};
// Set motor speed: 255 full ahead, −255 full reverse , 0 stop
void go(enum Motor m, int speed)
{
    digitalWrite(m == LEFT ? in1Pin : in3Pin, speed > 0 ? HIGH : LOW);
    digitalWrite(m == LEFT ? in2Pin : in4Pin, speed <= 0 ? HIGH : LOW);
    analogWrite(m == LEFT ? enAPin : enBPin, speed < 0 ? -speed : speed);
}

// Initial motor test :
// left motor forward then back
// right motor forward then back
void testMotors()
{
    static int speed[8] = {128, 255, 128, 0,
                           -128, -255, -128, 0};
    go(RIGHT, 0);
    for (unsigned char i = 0; i < 8; i++)
        go(LEFT, speed[i]), delay(200);
    for (unsigned char i = 0; i < 8; i++)
        go(RIGHT, speed[i]), delay(200);
}

void setup()
{
    // Configure input and pins
    pinMode(linePinLeft, INPUT);
    pinMode(linePinRight, INPUT);
    Serial.begin(9600);

    if (testDrive)
    {
        pinMode(enAPin, OUTPUT);
        pinMode(in1Pin, OUTPUT);
        pinMode(in2Pin, OUTPUT);
        pinMode(in3Pin, OUTPUT);
        pinMode(in4Pin, OUTPUT);
        pinMode(enBPin, OUTPUT);

        //Turn off the motors
        go(LEFT, 0);
        go(RIGHT, 0);

        //Test the motors
        //testMotors();
    }
}

void loop()
{

    int leftInp = digitalRead(linePinLeft);
    int rightInp = digitalRead(linePinRight);

    if (testDrive)
    {
        if (leftInp == 0 && rightInp == 0)
        {
            go(LEFT, 150);
            go(RIGHT, 150);
        }

        if (leftInp == 0 && rightInp != 0)
        {
            // turnright = move left wheel more than the right wheel
            go(LEFT, 150);
            go(RIGHT, 0);
        }

        if (leftInp != 0 && rightInp == 0)
        {
            // turnLeft = move right wheel more than the left wheel
            go(LEFT, 0);
            go(RIGHT, 150);
        }

        if (leftInp != 0 && rightInp != 0)
        {
            go(LEFT, 0);
            go(RIGHT, 0);
        }
        //Check next direction in 50ms
    }

    Serial.println("loop read");
    // Serial.println(digitalRead(linePinLeft));
    // Serial.println(digitalRead(linePinRight));
}
//12 -> lighton = 0
//10 -> lighton = 0
