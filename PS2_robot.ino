#include <PS2X_lib.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>

Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightmotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftmotor = AFMS.getMotor(4);

#define PS2_DAT        12 //updated   
#define PS2_CMD        11 //updated 
#define PS2_SEL        10 //updated 
#define PS2_CLK        13 //updated

//setting controller mode - still a little confused to what this actually does

#define pressures   false
#define rumble   false


int motorspeed = 0;

void setup() {
  AFMS.begin();
  rightmotor-> setSpeed(motorspeed);
  leftmotor-> setSpeed(motorspeed);
  rightmotor->run(FORWARD);
  leftmotor->run(FORWARD);
  rightmotor->run(RELEASE);
  leftmotor->run(RELEASE);

}

void loop() {
  rightmotor->run(FORWARD);
  leftmotor->run(FORWARD);
  rightmotor->setSpeed(motorspeed);
  leftmotor->setSpeed(motorspeed);
}
