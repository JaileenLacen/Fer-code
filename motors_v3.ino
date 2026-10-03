#include <DabbleESP32.h>

#define CUSTOM_SETTINGS
#define INCLUDE_GAMEPAD_MODULE

#define MAX_MOTOR_SPEED 255

// Motor driver 1 (Right Side)
#define PWMA_1 13
#define AIN1_1 14
#define AIN2_1 12
#define STBY_1 27
#define BIN1_1 26
#define BIN2_1 25
#define PWMB_1 33

// Motor driver 2 (Left Side)
#define PWMA_2 32
#define AIN1_2 19
#define AIN2_2 18
#define STBY_2 5
#define BIN1_2 4
#define BIN2_2 2
#define PWMB_2 15



void setMotorA(int speed) {
  digitalWrite(STBY_1, HIGH);
  digitalWrite(STBY_2, HIGH);

  if (speed > 0) {
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
  } else if (speed < 0) {
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
  } else {
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, LOW);
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, LOW);
  }

  ledcWrite(0, abs(speed)); // PWM CH_A1
  ledcWrite(2, abs(speed)); // PWM CH_A2
}

void setMotorB(int speed) {
  digitalWrite(STBY_1, HIGH);
  digitalWrite(STBY_2, HIGH);

  if (speed > 0) {
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
  } else if (speed < 0) {
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
  } else {
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, LOW);
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, LOW);
  }

  ledcWrite(1, abs(speed)); // PWM CH_B1
  ledcWrite(3, abs(speed)); // PWM CH_B2
}

void setMotorC(int speed) {
  digitalWrite(STBY_1, HIGH);
  digitalWrite(STBY_2, HIGH);

  if (speed > 0) {
    digitalWrite(AIN1_1, HIGH);
    digitalWrite(AIN2_1, LOW);
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, HIGH);
    digitalWrite(BIN1_1, HIGH);
    digitalWrite(BIN2_1, LOW);
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, HIGH);
  } else if (speed < 0) {
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, HIGH);
    digitalWrite(AIN1_2, HIGH);
    digitalWrite(AIN2_2, LOW);
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, HIGH);
    digitalWrite(BIN1_2, HIGH);
    digitalWrite(BIN2_2, LOW);
  } else {
    digitalWrite(AIN1_1, LOW);
    digitalWrite(AIN2_1, LOW);
    digitalWrite(AIN1_2, LOW);
    digitalWrite(AIN2_2, LOW);
    digitalWrite(BIN1_1, LOW);
    digitalWrite(BIN2_1, LOW);
    digitalWrite(BIN1_2, LOW);
    digitalWrite(BIN2_2, LOW);
  }

  ledcWrite(0, abs(speed)); // PWM CH_A1
  ledcWrite(2, abs(speed)); // PWM CH_A2
  ledcWrite(1, abs(speed)); // PWM CH_B1
  ledcWrite(3, abs(speed)); // PWM CH_B2
}

// void setMotorD(int speed) {
//   digitalWrite(STBY_1, HIGH);
//   digitalWrite(STBY_2, HIGH);

//   if (speed > 0) {
//     digitalWrite(BIN1_1, HIGH);
//     digitalWrite(BIN2_1, LOW);
//     digitalWrite(BIN1_2, LOW);
//     digitalWrite(BIN2_2, HIGH);
//   } else if (speed < 0) {
//     digitalWrite(BIN1_1, LOW);
//     digitalWrite(BIN2_1, HIGH);
//     digitalWrite(BIN1_2, HIGH);
//     digitalWrite(BIN2_2, LOW);
//   } else {
//     digitalWrite(BIN1_1, LOW);
//     digitalWrite(BIN2_1, LOW);
//     digitalWrite(BIN1_2, LOW);
//     digitalWrite(BIN2_2, LOW);
//   }

//   ledcWrite(0, abs(speed)); // PWM CH_A1
//   ledcWrite(2, abs(speed)); // PWM CH_A2
// }

void stopAllMotors() {
  setMotorA(0);
  setMotorB(0);
  setMotorC(0);
  // setMotorD(0);
}

void setUpPinModes() {
  pinMode(STBY_1, OUTPUT);
  pinMode(AIN1_1, OUTPUT);
  pinMode(AIN2_1, OUTPUT);
  pinMode(BIN1_1, OUTPUT);
  pinMode(BIN2_1, OUTPUT);

  pinMode(STBY_2, OUTPUT);
  pinMode(AIN1_2, OUTPUT);
  pinMode(AIN2_2, OUTPUT);
  pinMode(BIN1_2, OUTPUT);
  pinMode(BIN2_2, OUTPUT);

  // Setup PWM
  ledcSetup(0, 1000, 8); ledcAttachPin(PWMA_1, 0); // A1
  ledcSetup(1, 1000, 8); ledcAttachPin(PWMB_1, 1); // B1
  ledcSetup(2, 1000, 8); ledcAttachPin(PWMA_2, 2); // A2
  ledcSetup(3, 1000, 8); ledcAttachPin(PWMB_2, 3); // B2

  stopAllMotors();
}

void setup() {
  Serial.begin(9600);
  setUpPinModes();
  Dabble.begin("MyBluetoothCar");
}

void loop() {
  Dabble.processInput();

  if (GamePad.isUpPressed()) {
    setMotorC(MAX_MOTOR_SPEED);
    // setMotorD(MAX_MOTOR_SPEED);
  } else if (GamePad.isDownPressed()) {
    setMotorC(-MAX_MOTOR_SPEED);
    // setMotorD(-MAX_MOTOR_SPEED);
  } else if (GamePad.isLeftPressed()) {
    setMotorA(MAX_MOTOR_SPEED);  // Only motors A turn ON
    setMotorB(0);
  } else if (GamePad.isRightPressed()) {
    setMotorA(0);
    setMotorB(MAX_MOTOR_SPEED);  // Only motors B turn ON
  } else {
    stopAllMotors();
  }
}

