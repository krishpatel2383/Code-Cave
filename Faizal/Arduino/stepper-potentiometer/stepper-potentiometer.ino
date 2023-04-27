#include <AccelStepper.h>

#define dirPin 2
#define stepPin 5
#define motorInterfaceType 1

AccelStepper stepper = AccelStepper(motorInterfaceType, stepPin, dirPin);
int potpin = A0;

int val = 0;

void setup() {

  Serial.begin(9600);
  stepper.setMaxSpeed(3000);
  stepper.setAcceleration(1000);
  stepper.setSpeed(2500);
}


void loop() {

  val = analogRead(potpin);
  val = map(val, 0, 1023, 0, 3200);


  stepper.moveTo(val);
  while (stepper.distanceToGo() > 0 || stepper.distanceToGo() < 0) {
    stepper.run();
  }
  

  Serial.print(val);
  Serial.print("\t");
  Serial.println(stepper.currentPosition());

  delay(500);
}
