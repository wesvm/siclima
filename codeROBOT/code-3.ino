const int sensorPins[] = {2, 3};  
const int motorPins[2][2] = {{4, 5}, {6, 7}};  
const int enablePins[] = {9, 10};
const int MOTOR_SPEED = 90;     // <--- VELOCIDAD SEGURA
const int TURN_SPEED = 70;      // <--- VELOCIDAD PARA GIRO

void setup() { 
  for (int i = 0; i < 2; i++) {
    pinMode(sensorPins[i], INPUT);
  }
  for (int i = 0; i < 2; i++) {
    pinMode(motorPins[i][0], OUTPUT);
    pinMode(motorPins[i][1], OUTPUT);
    pinMode(enablePins[i], OUTPUT);
  } 
  Serial.begin(9600);
}

void loop() { 
  int sensorValues[2];
  for (int i = 0; i < 2; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
  }
 
  Serial.print("Left Sensor: ");
  Serial.print(sensorValues[0]);
  Serial.print(" | Right Sensor: ");
  Serial.println(sensorValues[1]);
 
  if (sensorValues[0] == HIGH && sensorValues[1] == HIGH) {
    moveForward();
  } else if (sensorValues[0] == LOW && sensorValues[1] == HIGH) {
    turnLeft();
  } else if (sensorValues[0] == HIGH && sensorValues[1] == LOW) {
    turnRight();
  } else {
    stopMotors();
  }
 
  delay(100);
}

void moveForward() {
  analogWrite(enablePins[0], MOTOR_SPEED);
  analogWrite(enablePins[1], MOTOR_SPEED);
  digitalWrite(motorPins[0][0], HIGH);
  digitalWrite(motorPins[0][1], LOW);
  digitalWrite(motorPins[1][0], HIGH);
  digitalWrite(motorPins[1][1], LOW);
}

void turnLeft() {
  analogWrite(enablePins[0], TURN_SPEED);
  analogWrite(enablePins[1], TURN_SPEED);
  digitalWrite(motorPins[0][0], LOW);   // Izq atrás
  digitalWrite(motorPins[0][1], HIGH);
  digitalWrite(motorPins[1][0], HIGH);  // Der adelante
  digitalWrite(motorPins[1][1], LOW);
}

void turnRight() {
  analogWrite(enablePins[0], TURN_SPEED);
  analogWrite(enablePins[1], TURN_SPEED);
  digitalWrite(motorPins[0][0], HIGH);  // Izq adelante
  digitalWrite(motorPins[0][1], LOW);
  digitalWrite(motorPins[1][0], LOW);   // Der atrás
  digitalWrite(motorPins[1][1], HIGH);
}

void stopMotors() {
  for (int i = 0 ; i < 2 ; i++) { 
    analogWrite(enablePins[i], 0);
  }
  for (int i = 0 ; i < 2 ; i++) {
    digitalWrite(motorPins[i][0], LOW);
    digitalWrite(motorPins[i][1], LOW);
  }
}