#include <Arduino.h>
#include <Servo.h>

const int PIN_PEN = 2;
const int PIN_LEFT = 3;
const int PIN_RIGHT = 4;

const int PEN_UP_ANGLE = 0;
const int PEN_DOWN_ANGLE = 180;

const int PEN_DIRECTION = PEN_DOWN_ANGLE > PEN_UP_ANGLE ? 1 : -1;

const int HOME_LEFT = 90;
const int HOME_RIGHT = 90;

const int PEN_DELAY = 10;    // mS per degree for pen servo
const int ANGLE_DELAY = 100; // mS per degree for arm servos

const float STEPS = 10;

Servo servoLeft;
Servo servoRight;
Servo servoPen;

// forward declarations

void home();
void penUp();
void penDown();
void moveServos(int angleLeft, int angleRight);

void go(){
    Serial.println("go");
    home();
    penDown();
moveServos(115, 50);
moveServos(114, 61);
moveServos(133, 88);
moveServos(150, 82);
}

void setup()
{
    Serial.begin(9600);
    servoLeft.attach(PIN_LEFT);
    servoRight.attach(PIN_RIGHT);
    servoPen.attach(PIN_PEN);
    go();
}

void loop()
{
   go();
    delay(1000);
}

void moveServos(int angleLeft, int angleRight)
{
   
Serial.print("Move Servos to : (");
Serial.print(angleLeft);
Serial.print(", (");
Serial.print(angleRight);
Serial.print(")\n");
   
    float previousLeft = servoLeft.read(); // last value written (cast to float)
    float previousRight = servoRight.read();

    float stepLeft = (float)(angleLeft - previousLeft) / STEPS;
    float stepRight = (float)(angleRight - previousRight) / STEPS;

    float currentLeft = previousLeft;
    float currentRight = previousRight;

    for (int i = 0; i <= STEPS; i++)
    {
        currentLeft += stepLeft;
        currentRight += stepRight;
 
        servoLeft.write(currentLeft);
        servoRight.write(currentRight);
        delay(ANGLE_DELAY);
    }
}

void penUp()
{

    /*
    int i = servoPen.read(); // last value written
    Serial.println(i);
    while (i != PEN_UP_ANGLE)
    {
                Serial.println(i);
        i += PEN_DIRECTION;
        servoPen.write(i);
        delay(PEN_DELAY);
    }
    */
   servoPen.write(0);
}

void penDown() // later : combine with above
{
     servoPen.write(180);
     /*
    int i = servoPen.read(); // last value written
    while (i != PEN_DOWN_ANGLE)
    {
        i -= PEN_DIRECTION;
        servoPen.write(i);
        delay(PEN_DELAY);
    }
    */
}

void home()
{
 
    penUp();
    moveServos(HOME_LEFT, HOME_RIGHT);
    delay(PEN_DELAY+ANGLE_DELAY);
}