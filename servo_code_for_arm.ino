/*this version is for stepper motors
 * this code will use C++
 * Use multiStepper to manage the different stepers to help move them to different positions
 * if needed to move the overall arm to a different position. include a way
 * to have the code take in the position values then
 */
#include <AccelStepper.h>
#include <MultiStepper.h>
#include <Servo.h>

//stepper motor pins
AccelStepper stepper1(AccelStepper::FULL2WIRE,2,3); //bottom joint rotate
AccelStepper stepper2(AccelStepper::FULL2WIRE,6,7); //Shoulder motors (both on the same signal)
AccelStepper stepper3(AccelStepper::FULL2WIRE,40,39);
AccelStepper stepper4(AccelStepper::FULL2WIRE,4,5); //axis 4 motor 
AccelStepper stepper5(AccelStepper::FULL2WIRE,8,9);
AccelStepper stepper6(AccelStepper::FULL2WIRE,12,13); //wrist motor

MultiStepper steppers; //have up to 10 of the steppers

//reformat data so you can just call the variable and use the index rather than
//have mulitple variables with the same value
const byte numChars = 128;
char receivedChars[numChars];
char tempChars[numChars];

//angles for the servos, received over serial
float q[6] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0};

//these are the steps that the angles are converted to
float s1 = 0.0;
float s2 = 0.0;
float s3 = 0.0;
float s4 = 0.0;
float s5 = 0.0;
float s6 = 0.0;

float grip = 0.0;
//has hte arm been calibrated bool
bool calibrated = false;

bool newData = false;
//describes the calibration -> used the next step of teh calibration
bool foundi[6] = {false, false, false, false, false, false};
//does started1-6 mean which servos have started?
bool startedi[6] = {false, false, false, false, false,false};

//is this the ranfes of each servo1-servo6
const float ranges[6] = {180, 360, 360, 270, 218, 360};

const float AXIS_I_MULT[6] = {25.5000, 5.33333, 16.4706, 10.0000, 4.80000, 4.80000};

//what are the searches?
const int search5 = -1*3200*AXIS_I_MULT[6]*(ranges[1]/360); //3200 comes from microstepping?
const int search6 = 3200*AXIS_I_MULT[5]*(ranges[2]/360);
const int search4 = 3200*AXIS_I_MULT[4]*(ranges[3]/360);
const int search3 = 2*800*AXIS_I_MULT[3]*(ranges[4]/360);
const int search2 = 1600*AXIS_I_MULT[2]*(ranges[5]/360);
const int search1 = 200*AXIS_I_MULT[1]*(ranges[6]/360);

const int axis1 = 48;
const int axis23 = 52;
const int axis4 = 51;
const int axis5 = 49
const int axis6 = 53;

//intilize the steppers
AccelStepper steppers[6];

Serial gripper;

void recvWriteStartEndMarkers() {
  static bool recvInProgress = false;
  static byte ndx = 0;
  char startMaker = '<';
  char endMaker = '>';
  char rc;

  while(Serial.available() > 0 && newData == false) {
    rc = Serial.read();

    if(recvInProgress == true) {
      if(rc != endMarker) {
        receivedChars[ndx] = rc;
        ndx++;
        if(ndx >= numChars) {
          ndx = numChars - 1;
        }
      }
      else {
        receivedChars[nxd] = '\0';
        recvInProgress = false;
        ndx = 0;
        newData = true;
      }
    }
    else if (rc == startMarker) {
      recvInProgress = true;
    }
  }
}

void calibrate() {
  //deactivate all the axis
  digitalWrite(31, LOW);
  digitalWrite(32, LOW);
  digitalWrite(33, LOW);
  digitalWrite(34, LOW);
  digitalWrite(35, LOW);
  digitalWrite(36, LOW);

  //turn the fan off
  digitalWrite(46, LOW);

  int sensor6 = d
}
//opens the gripper
void gripper_close() {
  gripper.write(130);
}

//closes the gripper
void gripper_open() {
  gripper.write(0);
}

// Splits the data into parts
void parseData() {
  char *strtokIndx;

  strtokIndx  = strtok(tempChars, ","); //gets the first part of the string
  
  // Assign parsed values to variables
  if (strtokIndx != NULL) q1 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  if (strtokIndx != NULL) q2 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  if (strtokIndx != NULL) q3 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  if (strtokIndx != NULL) q4 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  if (strtokIndx != NULL) q5 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  if (strtokIndx != NULL) q6 = atof(strtokIndx);

  strtokIndx = strtok(NULL, ",");
  grip = atof(strtokIndx);
}

void serialFlush() {
  if(newData == false) {
    while(Serial.available() > 0) {
      char t = Serial.read();
    }
  }
}

void angle_to_steps(){
  float s5_prelim = 3200*axis_5_mult*(q5/360); 
  float s6_prelim = 3200*axis_6_mult*(q6/360);
  s4 = 3200*axis_4_mult*(q4/360);
  s3 = 2*800*axis_3_mult*(q3/360);
  s2 = 2*1600*axis_2_mult*(q2/360);
  s1 = 800*axis_1_mult*(q1/360);
  s5 = s5_prelim + s6_prelim;
  s6 = s5_prelim - s6_prelim;
}

void update_position() {
  long positions[6]; //create an array of desired stepper positions
  position[0] = s1;
  position[1] = s2;
  position[2] = s3;
  position[3] = s4;
  position[4] = s5;
  position[5] = s6;
  steppers.moveTo(positions);
  //have the steppers move to a position
  steppers.runSpeedToPosition();
  
  if(grip > 0) {
    gripper_close();
  }
  else {
    gripper_open();
  }
  serialFlush();
  Serial.flush();
  Serial.write("Updated");
}

void setup() {
  Serial.begin(9600);
  gripper.attach(47);

  pinMode(axis1, INPUT);
  pinMode(axis23, INPUT);
  pinMode(50, INPUT);
  pinMode(axis4, INPUT);
  pinMode(axis23, INPUT); //i think this would be the 3rd one?
  pinMode(axis6, INPUT);

  pinMode(31, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(33, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(35, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(10, INPUT);

  //configure each of the steppers with a max speed and how fast they go
  //for the maxspeed -> 1 step per second
  stepper1.setMaxSpeed(1000);
  stepper1.setAcceleration(100);
  
  stepper2.setMaxSpeed(600);
  stepper2.setAcceleration(200);

  stepper3.setMaxSpeed(600);
  stepper3.setAcceleration(200);

  stepper4.setMaxSpeed(1000);
  stepper4.setAcceleration(200);

  stepper5.setMaxSpeed(8000);
  stepper5.setAcceleration(1000);

  stepper1.setMaxSpeed(800);
  stepper1.setAcceleration(100);  

  //give the multistepper the steppers to manage them
  //made it a forloop so at each iteration the stepper adds it 
  for(int i = 0; i < 6; ++i) {
    steppers.addStepper(stepper[i]);
    i++;
  }

  //wait for the power on signal reaches all parts of board-> arduino
  while(digitalRead(10) == 0) {
    digitalWrite(46, LOW);
    digitalWrite(31, LOW);
    digitalWrite(32, LOW);
    digitalWrite(33, LOW);
    digitalWrite(34, LOW);
    digtialWrite(35, LOW);
    digtialWrite(36, LOW);
    Serial.println("waiting....")
  }
  delay(2000);
}

void loop() {
  // put your main code here, to run repeatedly:
  int power = digitalRead(10);
  int sensor6 = digitalRead(axis6);
  int sensor5 = digitalRead(axis5);
  int sensor4 = ditialRead(axis4);
  int sensor3 = ditialRead(axis23);
  int sensor1 = digitalRead(axis1);

  if(power == 1 && calibrated) {
    //call the calibrate funciton to....
    calibrate(); 
    //one calibra func is called set the bool of it to true
    calbrated = true; 
  }
  else if(power == 0) {
    Serial.write("power loss");
  }

  recvWriteStartEndMarkers();
  if(newData = true) {
    strcpy(tempChars, receivedChars); // strcpy() function is used to copy the str[] string to the out_num[] array.

    parseData(); //this is a funciton
    for(int i = 0;  < 6; ++i) {
      Serial.print(q[i]);
      Serial.print(" ");
    }
    newData = false;
    serialFlush(); // figure out what this does
    delay(500);
    angle_to_steps();  //converts the angles into steps
    update_position();  //updates the position for us
  }
}