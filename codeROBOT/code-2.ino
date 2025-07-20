#include <Servo.h> // libreria

//  
const int trigPin = 11;   
const int echoPin = 12;  


Servo miServo; 
const int servoPin = 8;  
 
long leerDistanciaCm() {
  // cada seccion a 2 microsecondos
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 10 microsecondos por pulso despues de ejecutarse
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // tiempo (20ms) a un alcance aproximado de 3.4 metros. 
  long duracion = pulseIn(echoPin, HIGH, 20000);

  // rango de error
  if (duracion == 0) {
    return -1; // identificado para dar la notificacion
  }

  // calculo de distancia aproximada
  return duracion * 0.034 / 2;
}

void setup() {
  
  pinMode(trigPin, OUTPUT); 
  pinMode(echoPin, INPUT); 

   
  miServo.attach(servoPin);

  // 
  Serial.begin(9600);

  // posicion del servo a iniciar
  miServo.write(90);
  delay(500); // en tiempo lo qeu son 90 grados
}

void loop() { 
  for (int angulo = 0; angulo <= 180; angulo += 5) {
    miServo.write(angulo);  
    delay(30);  

    long distancia = leerDistanciaCm();  
    Serial.print("Angulo: ");  
    Serial.print(angulo);
    Serial.print(" grados, Distancia: ");  

    if (distancia == -1) {
      Serial.println("Fuera de rango"); // no detecta el rango
    } else {
      Serial.print(distancia); // imprime la distancia
      Serial.println(" cm");
    }
  }

  delay(500);  

  for (int angulo = 180; angulo >= 0; angulo -= 5) {
    miServo.write(angulo);  
    delay(30);  

    long distancia = leerDistanciaCm(); // reconocer distancia
    Serial.print("Angulo: ");
    Serial.print(angulo);
    Serial.print(" grados, Distancia: ");

    if (distancia == -1) {
      Serial.println("Fuera de rango");
    } else {
      Serial.print(distancia);
      Serial.println(" cm");
    }
  }
  delay(500); // la pausa
}
