#include <Arduino.h>
#include <Servo.h>

Servo servoA;
Servo servoB;
Servo servoP;

// hardware config
const int LED = 13; // Onboard LED
const int A_PIN = 3;
const int B_PIN = 4;
const int P_PIN = 2;
const unsigned long INACTIVITY_DELAY = 300000; // 5 minutes
const int MAX_ANGLE_STEP = 30;                 // max jump for each reaction

unsigned long lastChangeTime = millis();
int proximity = HIGH; // HIGH = no obstacle
int previousProximity = HIGH;
int currentAngle = 90;
int currentDirection = 1; // 1 for increasing angle, -1 for decreasing

// forward declarations of functions
void moveTo(Servo, int); // move to given angle
int twitch(Servo, int);  // random jump
void wave(Servo);        // slow move bach & forth
void once();
void show();
int direction(int, int);

void setup()
{
  Serial.begin(9600);
  servoA.attach(A_PIN);
  servoB.attach(B_PIN);
  servoP.attach(P_PIN);
  pinMode(LED, OUTPUT);

  delay(500);
  // wave(servoP);
  servoP.write(0);
  Serial.println("A  B  P");
  once();
}

void loop()
{
  wave(servoA);
  // wave(servoB);
  delay(1000);
}

void once()
{
  show();
  servoP.write(0);
  delay(1000);
  servoA.write(90);
  delay(1000);
  servoB.write(90);
  show();
}

void show()
{
  Serial.print(servoA.read());
  Serial.print("   ");
  Serial.print(servoB.read());
  Serial.print("   ");
  Serial.print(servoP.read());
  Serial.println("   ");
}

void moveTo(Servo servo, int target)
{
  int current = servo.read();
  int dir = direction(current, target);
  while (abs(current - target) > 2)
  {
    current = servo.read();
    int aim = current + dir;
    servo.write(aim);
    delay(10);
  }
}

int direction(int current, int target)
{
  if (target > current)
    return 1;
  if (current > target)
    return -1;
  return 0;
}

void wave(Servo servo)
{
  for (int i = 20; i < 160; i++)
  {
    moveTo(servo, i);
  }
  for (int i = 160; i > 20; i--)
  {
    moveTo(servo, i);
  }
  show();
}
