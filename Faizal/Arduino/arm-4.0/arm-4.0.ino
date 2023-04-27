#include <AccelStepper.h>

//#define dirPin1 2
//#define stepPin1 6
//#define dirPin2 3
//#define stepPin2 7
//#define dirPin3 4
//#define stepPin3 8
//#define dirPin4 5
//#define stepPin4 9

#define dirPin1 2
#define stepPin1 5
#define dirPin2 4
#define stepPin2 7
#define dirPin3 8
#define stepPin3 9
#define dirPin4 10
#define stepPin4 11


AccelStepper stepper_1 = AccelStepper(1, stepPin1, dirPin1);
AccelStepper stepper_2 = AccelStepper(2, stepPin2, dirPin2);
AccelStepper stepper_3 = AccelStepper(3, stepPin3, dirPin3);
AccelStepper stepper_4 = AccelStepper(4, stepPin4, dirPin4);

//potentiometer reading
int potpin1 = A0;
int potpin2 = A1;
int potpin3 = A2;
int potpin4 = A3;

//Recording button
const int recordBtnPin = 3;
const int recordLedPin =  13;
int recordBtnState = 0;

//Play button
const int playBtnPin = 6;
const int playLedPin =  12;
int playBtnState = 0;

//  Potentiometer reading
int pot1Reading = 0;
int pot2Reading = 0;
int pot3Reading = 0;
int pot4Reading = 0;

//Motor position
int motor1_pos;
int motor2_pos;
int motor3_pos;
int motor4_pos;

//motor memory to save positions.
int memory[400];

int motorNo;
int motor_Position;

//memory indexs
int index = 0;

//previous position
int prev_pos1;
int prev_pos2;
int prev_pos3;
int prev_pos4;

//current position
int current_pos1;
int current_pos2;
int current_pos3;
int current_pos4;

void setup() {

  Serial.begin(9600);

  //  Motors configuration
  stepper_1.setMaxSpeed(4000);
  stepper_1.setAcceleration(3000);
  stepper_1.setSpeed(3000);

  stepper_2.setMaxSpeed(4000);
  stepper_2.setAcceleration(3000);
  stepper_2.setSpeed(3000);

  stepper_3.setMaxSpeed(4000);
  stepper_3.setAcceleration(3000);
  stepper_3.setSpeed(3000);

  stepper_4.setMaxSpeed(4000);
  stepper_4.setAcceleration(3000);
  stepper_4.setSpeed(3000);

  //  Record button & Led configuration
  pinMode(recordBtnPin, INPUT);
  digitalWrite(recordBtnPin, LOW);
  pinMode(recordLedPin, OUTPUT);
  digitalWrite(recordLedPin, LOW);

  //  Play button & Led configuration
  pinMode(playBtnPin, INPUT);
  digitalWrite(playBtnPin, LOW);
  pinMode(playLedPin, OUTPUT);
  digitalWrite(playLedPin, LOW);
  
  Serial.println("Press Record button to record and PLay button to Play...");
}

void getReading() {

  pot1Reading = analogRead(potpin1);
  motor1_pos = map(pot1Reading, 0, 1023, 0, 3200);
  stepper_1.moveTo(motor1_pos);
  while (stepper_1.distanceToGo() > 0 || stepper_1.distanceToGo() < 0) {
    stepper_1.run();
  }

  pot2Reading = analogRead(potpin2);
  motor2_pos = map(pot2Reading, 0, 1023, 0, 3200);
  stepper_2.moveTo(motor2_pos);
  while (stepper_2.distanceToGo() > 0 || stepper_2.distanceToGo() < 0) {
    stepper_2.run();
  }

  pot3Reading = analogRead(potpin3);
  motor3_pos = map(pot3Reading, 0, 1023, 0, 3200);
  stepper_3.moveTo(motor3_pos);
  while (stepper_3.distanceToGo() > 0 || stepper_3.distanceToGo() < 0) {
    stepper_3.run();
  }

  pot4Reading = analogRead(potpin4);
  motor4_pos = map(pot4Reading, 0, 1023, 0, 3200);
  stepper_4.moveTo(motor4_pos);
  while (stepper_4.distanceToGo() > 0 || stepper_4.distanceToGo() < 0) {
    stepper_4.run();
  }
}

void loop() {

  getReading();

  prev_pos1 = motor1_pos;
  prev_pos2 = motor2_pos;
  prev_pos3 = motor3_pos;
  prev_pos4 = motor4_pos;
  recordBtnState = digitalRead(recordBtnPin);
  playBtnState = digitalRead(playBtnPin);

  //For recording when record button press
  if (recordBtnState == HIGH) {

    Serial.println("Recording the moves.....");
    digitalWrite(recordLedPin, HIGH);

    getReading();

    if (prev_pos1 != motor1_pos) { // motor one

      memory[index] = motor1_pos + 0;
      index++;
      Serial.print("saved : ");
      Serial.print(memory[index - 1]);
      Serial.print("\tIndex : ");
      Serial.print(index - 1);
      Serial.println("\tmotor 1");
    }

    if (prev_pos2 != motor2_pos) { // motor two
      memory[index] = motor2_pos + 1600;
      index++;
      Serial.print("saved : ");
      Serial.print(memory[index - 1]);
      Serial.print("\tIndex : ");
      Serial.println(index - 1);
      Serial.println("\tmotor 2");
    }

    if (prev_pos3 != motor3_pos) { // motor three
      memory[index] = motor3_pos + 3200;
      index++;
      Serial.print("saved : ");
      Serial.print(memory[index - 1]);
      Serial.print("\tIndex : ");
      Serial.println(index - 1);
      Serial.println("\tmotor 3");
    }

    if (prev_pos4 != motor4_pos) { // motor four
      memory[index] = motor4_pos + 4800;
      index++;
      Serial.print("saved : ");
      Serial.print(memory[index - 1]);
      Serial.print("\tIndex : ");
      Serial.println(index - 1);
      Serial.println("\tmotor 4");
    }


  } else {
    digitalWrite(recordLedPin, LOW);
  }

  //For Playing when play button press
  if (playBtnState == HIGH && recordBtnState != HIGH) {
    Serial.print("\n");
    Serial.println("Playing the recording.....");

    digitalWrite(playLedPin, HIGH);

    for (int i = 0 ; i < index; i++) {
      motorNo = memory[i] / 1600;
      motor_Position = memory[i] % 1600;

      switch (motorNo) {
        case 0:
          stepper_1.moveTo(motor_Position);
          while (stepper_1.distanceToGo() > 0 || stepper_1.distanceToGo() < 0) {
            stepper_1.run();
          }
          Serial.print(motor_Position);
          Serial.print("\t");
          break;

        case 1:
          stepper_2.moveTo(motor_Position);
          while (stepper_2.distanceToGo() > 0 || stepper_2.distanceToGo() < 0) {
            stepper_2.run();
          }
          Serial.print(motor_Position);
          Serial.print("\t");
          break;


        case 2:
          stepper_3.moveTo(motor_Position);
          while (stepper_3.distanceToGo() > 0 || stepper_3.distanceToGo() < 0) {
            stepper_3.run();
          }
          Serial.print(motor_Position);
          Serial.print("\t");
          break;

        case 3:
          stepper_4.moveTo(motor_Position);
          while (stepper_4.distanceToGo() > 0 || stepper_4.distanceToGo() < 0) {
            stepper_4.run();
          }
          Serial.print(motor_Position);
          Serial.print("\t");
          break;
      }
    }

  } else {
    digitalWrite(playLedPin, LOW);
  }

  delay(500);
}
