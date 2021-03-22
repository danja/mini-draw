#include <Arduino.h>
// #include <utility>   // for pair

// http://www.cplusplus.com/reference/utility/pair/pair/

//#include <math.h> //for Arduino IDE
// #include "hardware/tools/avr/avr/include/math.h" //for vscode
#include <Servo.h>

// mine
// const int A_PIN = 3;
// const int B_PIN = 4;
// const int P_PIN = 2;

// his
/*
#define S1_PIN 3
#define S2_PIN 4
#define S3_PIN 2
*/
#define S1_PIN 3
#define S2_PIN 4
#define S3_PIN 2

#define S1_POS_X 0
#define S1_POS_Y 0

#define S2_POS_X 50
#define S2_POS_Y 0

#define S1_OFFSET 2.5
#define S2_OFFSET -7.5

#define ARM_LEN_1 85 
#define ARM_LEN_2 100
#define ARM_LEN_3 35

#define LIFT_HEIGHT 180 
// 90
#define BASE_HEIGHT 40
#define LIFTING_SPEED 7 //lower is faster

#define STEPS_PER_MM 5
#define CIRCLE_PRECISION 0.05
#define MS_PER_DEG 5.0 //1.7

Servo servo_A;
Servo servo_B;
Servo servo_P;

double current_x = 0;
double current_y = 0;
double current_s1_deg = 0;
double current_s2_deg = 0;
bool lifted = false;

void move_to(double, double);
void pen_up();
void pen_down();
void draw_line(double, double, double, double, bool = false);
void draw_circle(double, double, double);

void pen_up()
{

   for(int i = servo_P.read(); i > 0; i--)
  {
    servo_P.write(i);
   // delay(LIFTING_SPEED);
   delay(20);
  }
}


void pen_down()
{
  for(int i = servo_P.read(); i < 180; i++)
  {
    servo_P.write(i);
   // delay(LIFTING_SPEED);
   delay(20);
  }
}

void draw_line(double x1, double y1, double x2, double y2, bool without_lifting)
{
  move_to(x1, y1);

  if(lifted)
    pen_down();
  
  double dx = x2 - x1;
  double dy = y2 - y1;  
  double c = round(STEPS_PER_MM * sqrt(dx*dx + dy*dy));
  
  for(int i = 0; i <= c; i++)
  {
    move_to(x1 + i*dx/c, y1 + i*dy/c);
  }

  if(!without_lifting)
    pen_up();
}

void draw_circle(double x, double y, double radius)
{
  move_to(x+cos(0)*radius, y+sin(0)*radius);
  
  if(lifted)
    pen_down();
  
  for(double r = CIRCLE_PRECISION; r <= M_PI*2; r += CIRCLE_PRECISION)
  {
    //draw_line(current_x, current_y, x+cos(r)*radius, y+sin(r)*radius, true);
    move_to(x+cos(r)*radius, y+sin(r)*radius);
  }
  
  pen_up();
}

inline double cosine_angle_rule(double a, double b, double c)
{
  // cosine rule for angle between c and a
  return acos((a * a + c * c - b * b) / (2 * a * c));
}

inline double cosine_side_rule(double A, double b, double c)
{
  return sqrt(b*b+c*c-2*b*c*cos(A));
}

inline double rad_to_deg(double rad)
{
  return rad * (180.0 / M_PI);
}

inline double pitagoras(double b, double c)
{
  return sqrt(b*b + c*c);
}

//for a better understanding take look at the following image:
//https://github.com/andres-zibula/project-images/blob/master/parallel_scara_stylus/parallel_scara_stylus.jpeg
void move_to(double x, double y)
{
  if (current_x == x && current_y == y)
    return;

  double L4 = cosine_side_rule(M_PI - M_PI/4.0, ARM_LEN_2, ARM_LEN_3);
  double epsilon = cosine_angle_rule(L4, ARM_LEN_2, ARM_LEN_3);
  double d3 = pitagoras(S2_POS_X - x, y - S2_POS_Y);
  double theta2 = atan2(y, (S2_POS_X - x)) + cosine_angle_rule(d3, L4, ARM_LEN_1);
  
  double x4 = S2_POS_X + ARM_LEN_1*cos(M_PI - theta2);
  double y4 = S2_POS_Y + ARM_LEN_1*sin(M_PI - theta2);
  
  double delta = atan2((x4-x), (y-y4));
  
  double x1 = x + ARM_LEN_3*sin(delta-epsilon);
  double y1 = y - ARM_LEN_3*cos(delta-epsilon);
  
  double d1 = pitagoras(x1 - S1_POS_X, y1 - S1_POS_Y);
  double theta1 = atan2((y1 - S1_POS_Y), (x1 - S1_POS_X)) + cosine_angle_rule(d1, ARM_LEN_2, ARM_LEN_1);

  double s1deg = rad_to_deg(theta1);
  double s2deg = rad_to_deg(M_PI - theta2);

//  int current_A = servo_A.read(); // previous written value
//  int current_B = servo_B.read(); // not read from servo


  servo_A.write(s1deg + S1_OFFSET);
  servo_B.write(s2deg + S2_OFFSET);
  
  double max_dist = max(abs(current_s1_deg - s1deg), abs(current_s2_deg - s2deg));
  int delay_servo = ceil(MS_PER_DEG*ceil(max_dist));

  if (delay_servo < 10)
    delay_servo = 10;
  
  current_x = x;
  current_y = y;
  current_s1_deg = s1deg;
  current_s2_deg = s2deg;

  delay(delay_servo);
}

void setup()
{
  servo_A.attach(S1_PIN);
  servo_B.attach(S2_PIN);
  servo_P.attach(S3_PIN);
 // servo_A.write(90);
 // servo_B.write(90);
 // servo_P.write(90);

 /*
  move_to(10, 10);
pen_down();
   draw_line(10, 10, 11, 11);
   pen_up();
  */

 /*
  pen_up();
    servo_A.write(90);
  servo_B.write(90);
pen_down();

  servo_A.write(100);
  servo_B.write(100);
  pen_up();
*/
  
  // draw_line(-25, 130, 75, 130);
  // draw_line(-25, 150, 75, 150);
  // draw_line(-25, 170, 75, 170);

  // draw_line(-25, 130, 75, 130);
  // draw_line(75, 170, -25, 170);

  draw_circle(0, 150, 32);
  
servo_A.write(90);
 servo_B.write(90);
servo_P.write(180);
  
  
  // draw_circle(25, 150, 32);
  // draw_circle(50, 150, 32);
  
  // pen_up();
// pen_down();
// pen_up();
}

void loop()
{
  delay(1000);
}
