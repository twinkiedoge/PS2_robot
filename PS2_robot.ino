
#include <PS2X_lib.h>
#include <Adafruit_MotorShield.h>
#include <Wire.h>
//--------------------------stuff that has to do with PS2 setup--------------------------------

#define PS2_DAT        12 //updated   
#define PS2_CMD        11 //updated 
#define PS2_SEL        10 //updated 
#define PS2_CLK        13 //updated

//setting controller mode - still a little confused to what this actually does

#define pressures   false
#define rumble   false

int error = 0;
byte type = 0;
byte vibrate = 0;
PS2X ps2x;


//--------------------------stuff that has to do with motor setup--------------------------------

int motorspeed = 0;
float sensitivity = 0.8;
Adafruit_MotorShield AFMS = Adafruit_MotorShield();
Adafruit_DCMotor *rightmotor = AFMS.getMotor(3);
Adafruit_DCMotor *leftmotor = AFMS.getMotor(4);


void setup() {
  Serial.begin(57600);
  delay(300);
  Serial.println("serial initialized ");
  
  //motor
  AFMS.begin();
  rightmotor-> setSpeed(motorspeed);
  leftmotor-> setSpeed(motorspeed);
  rightmotor->run(FORWARD);
  leftmotor->run(FORWARD);
  rightmotor->run(RELEASE);
  leftmotor->run(RELEASE);

  //--------------------------from PS2X library example Bill Porter?--------------------------------------------------------------
error = ps2x.config_gamepad(PS2_CLK, PS2_CMD, PS2_SEL, PS2_DAT, pressures, rumble);
  
  if(error == 0){
    Serial.print("Found Controller, configured successful ");
    Serial.print("pressures = ");
  if (pressures)
    Serial.println("true ");
  else
    Serial.println("false");
  Serial.print("rumble = ");
  if (rumble)
    Serial.println("true)");
  else
    Serial.println("false");
    Serial.println("Try out all the buttons, X will vibrate the controller, faster as you press harder;");
    Serial.println("holding L1 or R1 will print out the analog stick values.");
    Serial.println("Note: Go to www.billporter.info for updates and to report bugs.");
  }  
  else if(error == 1)
    Serial.println("No controller found, check wiring, see readme.txt to enable debug. visit www.billporter.info for troubleshooting tips");
   
  else if(error == 2)
    Serial.println("Controller found but not accepting commands. see readme.txt to enable debug. Visit www.billporter.info for troubleshooting tips");

  else if(error == 3)
    Serial.println("Controller refusing to enter Pressures mode, may not support it. ");
  
  
  type = ps2x.readType(); 
  switch(type) {
    case 0:
      Serial.print("Unknown Controller type found ");
      break;
    case 1:
      Serial.print("DualShock Controller found ");
      break;
    case 2:
      Serial.print("GuitarHero Controller found ");
      break;
  case 3:
      Serial.print("Wireless Sony DualShock Controller found ");
      break;
   }
//----------------------------end of code used from example-----------------------------------------

}

void loop() {
ps2x.read_gamepad(false, vibrate); 
    rightmotor->run(FORWARD);
    leftmotor->run(FORWARD);
  if(ps2x.Button(PSB_R1)) {
    int rightstickx = ps2x.Analog(PSS_RX);
    if(rightstickx>134){
      int rspeed = (rightstickx*sensitivity);
      int lspeed = 255-rspeed;
      rightmotor->setSpeed(rspeed);
      leftmotor->setSpeed(lspeed);
    }else if(rightstickx<120){
      int lspeed = ((rightstickx*-1)+255)*sensitivity;
      int rspeed = 255-lspeed;
      rightmotor->setSpeed(rspeed);
      leftmotor->setSpeed(lspeed);
    }else{
      rightmotor->setSpeed(200);
      leftmotor->setSpeed(200);
    }
   }
   if (ps2x.NewButtonState(PSB_CROSS)){
      rightmotor->setSpeed(1000);
      leftmotor->setSpeed(1000);
      //delay(100);
      rightmotor->setSpeed(0);
      leftmotor->setSpeed(0);
      Serial.println("stop");
  }
}
