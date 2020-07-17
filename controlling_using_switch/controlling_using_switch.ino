#include <Servo.h>
Servo servoOut;

#include <Stepper.h>
// Define number of steps per rotation:
const int stepsPerRevolution = 2048;
Stepper myStepper = Stepper(stepsPerRevolution, 8, 10, 9, 11);

//analog joystick
int Xinput = A0;
int Yinput = A1;
float posX;
int posY;
int inputSw = 7;
float sw;

bool reset = true;

//servo
int servoOutPin = 3;
float servoPos = 90;

//boolean for control
boolean servoControlOn = false;
void setup() {
  myStepper.setSpeed(10);

  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  pinMode(Xinput, INPUT);
  pinMode(Yinput, INPUT);
  pinMode(inputSw, INPUT);
  digitalWrite(inputSw, HIGH);

  servoOut.attach(servoOutPin);
  servoOut.write(servoPos);
}
void loop() {
  posX = analogRead(Xinput);
  posY = analogRead(Yinput);
  sw = digitalRead(inputSw);

  if (posY > 650) {
    //Serial.println("Right");
    myStepper.step(25);
  } else if (posY < 350) {
    // Serial.println("Left");
    myStepper.step(-25);
  }
  //Serial.println(sw);


  if (sw == 0) {
    if (servoControlOn == false && reset == true) {
      servoControlOn = true;
      reset = false;
        Serial.println("hey");
    } else if(reset == true && servoControlOn == true) {
      servoControlOn = false;
      reset = false;
        Serial.println("heyo");
    }
  }
  if(sw == 1){
    reset = true;
  }
   if(reset == true){
    Serial.println("rested");
   }else{
    Serial.println("not reseted");
   }

  if (servoControlOn == true) {
    servoPos = (posX / 1000) * 180;
    //Serial.println(posX / 1000);
    servoOut.write(servoPos);
  } else {
    servoOut.write(servoPos);
  }
}
