// Definir pines
const int sensorPins[] = {2, 3}; // Pines de los sensores
const int motorPins [] [2] = {{4, 5), (6, 7}}; // Pines de los motores
const int enablePins[] = {9, 10); // Pines de habilitación de los motores

void setup() {
  // Configurar pines de los sensores
  for (int i = 0; i < 2; i++) {
    pinMode (sensorPins [i], INPUT);
  }


  // Configurar pines del motor
  for (int i = 0; i < 2; i++) {
    pinMode (motorPins [i] [0], OUTPUT);
    pinMode (motorPins [i] [1], OUTPUT);
    pinMode (enablePins[i], OUTPUT);
  }
  // Inicializar la comunicación serial
  Serial.begin(9600);
}

void loop() {
  // Leer los valores de los sensores
  int sensorValues[2];
  for (int i = 0; i < 2; i++) {
    sensorValues[i] = digitalRead(sensorPins[i]);
  }

  // Mostrar los valores de los sensores en el monitor serial
  Serial.print("Left Sensor: ");
  Serial.print(sensorValues[0]);
  Serial.print(" | Right Sensor: ");
  Serial.println(sensorValues[1]);

  // Controlar el motor basado en los valores de los sensores == HIGH) {
  if (sensorValues[0] == HIGH && sensorValues[1] == HIGH) {
    // Ambos sensores detectan línea, avanzar recto move Forward();
  } else if (sensorValues[0] == LOW && sensorValues[1] == HIGH) {
    // Solo el sensor derecho detecta línea, girar a la izquierda turnLeft();
  } else if (sensorValues[0] == HIGH && sensorValues [1] == LOW) {
    // Solo el sensor izquierdo detecta línea, girar a la derecha 
    turnRight();
  } else {
    // Ninguno de los sensores detecta línea, detenerse 
    stopMotors();
  }

  // Esperar un poco antes de la siguiente lectura 
  delay(100);
}

void moveForward() {
}
for (int i = 0 ; i < 2 ; i++) {
    analogWrite (enablePins[i], 255);
  }
  digitalWrite(motorPins [0] [0], HIGH);
  digitalWrite (motorPins [0] [1], LOW);
  digitalWrite(motorPins [1] [0], HIGH);
  digitalWrite (motorPins [1] [1], LOW);
}

void turnLeft() {
  analogWrite (enablePins[0], 255);
  analogWrite (enablePins [1], 255);
  digitalWrite (motorPins [0] [0], LOW);
  digitalWrite (motorPins [0] [1], HIGH);
  digitalWrite(motorPins [1] [0], HIGH);
  digitalWrite (motorPins [1] [1], LOW);
}

void turnRight() {
  analogWrite (enablePins[0], 255);
  analogWrite (enablePins [1], 255);
  digitalWrite(motorPins [0] [0], HIGH);
  digitalWrite(motorPins [0] [1], LOW);
  digitalWrite(motorPins [1] [0], LOW);
  digitalWrite (motorPins [1] [1], HIGH);
}

void stopMotors() {
  for (int i = 0 ; i < 2 i++) { 
    analogWrite(enablePins[i], 0);
  }
  for (int i = 0 ; i < 2 i++) {
    digitalWrite(motorPins [i] [0], LOW);
    digitalWrite (motorPins [i] [1], LOW);
  }
}
