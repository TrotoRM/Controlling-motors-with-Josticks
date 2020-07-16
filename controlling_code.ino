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

//servo
int servoOutPin = 3;
float servoPos = 90;
void setup() {
  myStepper.setSpeed(10);

  // Begin Serial communication at a baud rate of 9600:
  Serial.begin(9600);

  pinMode(Xinput, INPUT);
  pinMode(Yinput, INPUT);
  servoOut.attach(servoOutPin);
  servoOut.write(servoPos);
}
void loop() {
  posX = analogRead(Xinput);
  posY = analogRead(Yinput);

  if (posY > 650) {
    Serial.println("Right");
    myStepper.step(25);
  } else if (posY < 350) {
    Serial.println("Left");
    myStepper.step(-25);
  }
    
    servoPos = (posX / 1000) * 180;
    Serial.println(posX/1000);
    servoOut.write(servoPos);
}
