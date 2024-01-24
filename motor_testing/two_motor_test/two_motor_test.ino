#define PUL1_PIN    46
#define DIR1_PIN    A7
#define EN1_PIN     A8
#define PUL2_PIN    A6
#define DIR2_PIN    A7
#define EN2_PIN     A2
  
class stepperMotor{
  public:
     
  void stop(void){
    enable = 0;
    digitalWrite(enPin,HIGH);
    
  }
  
  void start(void){
    enable = 1;
    digitalWrite(enPin,LOW);
    
  }
  
  void init(int _pulsePin, int _dirPin, int _enPin, unsigned long _delayTime, bool _direction){
    pulsePin      = _pulsePin;
    dirPin        = _dirPin;
    enPin         = _enPin;
    delayTime     = _delayTime;
    direction     = _direction;
      
    togglePulse   = LOW;
    enable        = 0;
      
    pinMode(pulsePin, OUTPUT);
    pinMode(dirPin, OUTPUT);
    pinMode(enPin, OUTPUT);
  }
  
  void control(void){
    currentTime = micros();
    digitalWrite(dirPin, direction);
    if(enable == 1){
      if( (currentTime - deltaTime) > delayTime ){
        pulseCount++;
 
        // Each HIGH or LOW is a "pulse"
        // But each step of the motor requires two "pulses"
        if(pulseCount % 2 == 0){
          stepCount++;
        }
  
        togglePulse = togglePulse == LOW ? HIGH : LOW;
        digitalWrite(pulsePin, togglePulse);
        deltaTime = currentTime;
      }
    }
  }
  
  void changeDirection(bool _direction){
    direction = _direction;
  }
  
  unsigned long steps(void){
    return stepCount;
  }
  
  void changeSpeed(unsigned long _speed){
    delayTime = _speed;
  }
    
  private:
  unsigned long delayTime, deltaTime, currentTime;
  unsigned long pulseCount = 0;
  unsigned long stepCount = 0;
  int pulsePin, dirPin, enPin;
  bool direction, togglePulse, enable;
};
  
stepperMotor stepperOne, stepperTwo;
  
void setup() {
  stepperOne.init(PUL1_PIN,DIR1_PIN,EN1_PIN,1000,HIGH);
  stepperTwo.init(PUL2_PIN,DIR2_PIN,EN2_PIN,1000,HIGH);
  stepperOne.start();
  stepperTwo.start();
  Serial.begin(9600);
}
  
void loop() {
  // stepperOne.control();
  stepperTwo.control();
  Serial.println(stepperOne.steps());
  Serial.println(stepperTwo.steps());
  
  // if(stepperOne.steps() == 200){
  //   stepperOne.changeDirection(LOW);
  //   stepperOne.changeSpeed(600);
  // }
}