

int pwmPin = A9;
float pulseLen = 0.0;

const int stepPin0 = A0; 
const int dirPin0 = A1; 
const int enable0 = 38;

int t = 1500;
int ty = 1000;
int steps = 200;

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
  delay(1000);
}

void setup() {
  // put your setup code here, to run once:
  pinMode(stepPin0,OUTPUT); 
  pinMode(dirPin0,OUTPUT);
  pinMode(enable0, OUTPUT);

  Serial.begin(9600);
  pinMode(pwmPin,INPUT);

}

void loop() {
  // put your main code here, to run repeatedly:
  float vals[5];
  /*for (int i = 0; i < 5; i++) {
    vals[i] = pulseIn(pwmPin, HIGH);
    Serial.println(vals[i]);
  }
  */
  //pulseLen = pulseIn(pwmPin, HIGH);
  // rotate_x();
  float pos = analogRead(pwmPin);
  // Serial.println(analogRead(A1));
  Serial.println(pos);
  // Move stepper motor here

}
