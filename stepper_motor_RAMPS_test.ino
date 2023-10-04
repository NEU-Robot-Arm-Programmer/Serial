// defines pins numbers

//z axis - base, y axis - elbow , x -axis - 2 nd elbow idk for sure
//for stepper base
const int stepPin0 = A0; 
const int dirPin0 = A1; 
const int enable0 = 38;

//for stepper y axis
const int stepPin1 = A6; 
const int dirPin1 = A7; 
const int enable1 = A2;

//for stepper z axis
const int stepPin2 = 46; 
const int dirPin2 = A7; 
const int enable2 = A8;

int t = 1500;
int steps = 1600;

void rotate_z(){
  digitalWrite(enable2,LOW);
  digitalWrite(dirPin2,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin2,HIGH); 
    delayMicroseconds(t); 
    digitalWrite(stepPin2,LOW); 
    delayMicroseconds(t); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin2,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin2,HIGH);
    delayMicroseconds(t);
    digitalWrite(stepPin2,LOW);
    delayMicroseconds(t);
  }
  delay(1000);;
}


void rotate_y(){
  digitalWrite(enable1,LOW);
  digitalWrite(dirPin1,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin1,HIGH); 
    delayMicroseconds(t); 
    digitalWrite(stepPin1,LOW); 
    delayMicroseconds(t); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin1,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin1,HIGH);
    delayMicroseconds(t);
    digitalWrite(stepPin1,LOW);
    delayMicroseconds(t);
  }
  delay(1000);;
}

void rotate_x(){
  digitalWrite(enable0,LOW);
  digitalWrite(dirPin0,HIGH); // Enables the motor to move in a particular direction
  // Makes 200 pulses for making one full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin0,HIGH); 
    delayMicroseconds(t); 
    digitalWrite(stepPin0,LOW); 
    delayMicroseconds(t); 
  }
  delay(1000); // One second delay
  
  digitalWrite(dirPin0,LOW); //Changes the rotations direction
  // Makes 400 pulses for making two full cycle rotation
  for(int x = 0; x < steps; x++) {
    digitalWrite(stepPin0,HIGH);
    delayMicroseconds(t);
    digitalWrite(stepPin0,LOW);
    delayMicroseconds(t);
  }
  delay(1000);;
}


void setup() {
  // Sets the two pins as Outputs
  pinMode(stepPin0,OUTPUT); 
  pinMode(dirPin0,OUTPUT);
  pinMode(enable0, OUTPUT);

    pinMode(stepPin1,OUTPUT); 
  pinMode(dirPin1,OUTPUT);
  pinMode(enable1, OUTPUT);

    pinMode(stepPin2,OUTPUT); 
  pinMode(dirPin2,OUTPUT);
  pinMode(enable2, OUTPUT);
}

void loop() {
 rotate_z();
 delay(10);
 rotate_x();
 delay(10);

}
