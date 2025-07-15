// Pines del L298N
const int ENA = 9; // Motor izquierdo
const int ENB = 10; // Motor derecho
const int IN1 = 4;
const int IN2 = 5;
const int IN3 = 6;
const int IN4 = 7;

// Velocidades máximas (ajusta según pruebas)
const int VELOCIDAD_BASE_IZQ = 58;   // Baja para menos consumo y calor
const int VELOCIDAD_BASE_DER = 67;

// Velocidad para giros (más baja)
const int VEL_GIRO_IZQ = 43;
const int VEL_GIRO_DER = 47;

// Tiempos estimados (ajusta según pruebas)
const unsigned long TIEMPO_1M = 1800;  // ms para 1 metro
const unsigned long TIPO_05M = 900;  // ms para 0.5 metro
const unsigned long TIEMPO_GIRO_90 = 320; // ms para 90 grados (ajusta en pruebas)

// --------- Rampas de aceleración/desaceleración ---------
void rampaAceleracion(int velFinalIzq, int velFinalDer, bool haciaAdelante) {
  int paso = 5; // Incremento de velocidad en cada paso
  int vMax = max(velFinalIzq, velFinalDer); // Tomar la velocidad más alta como referencia para el bucle

  for (int v = 0; v <= vMax; v += paso) {
    // Calcular velocidades proporcionales para cada motor en cada paso
    int currentVelIzq = map(v, 0, vMax, 0, velFinalIzq);
    int currentVelDer = map(v, 0, vMax, 0, velFinalDer);

    if (haciaAdelante) {
      adelante(currentVelIzq, currentVelDer);
    } else {
      atras(currentVelIzq, currentVelDer);
    }
    delay(25); // Pequeña pausa para una aceleración más suave
  }
}

// Rampa de desaceleración gradual
// 'haciaAdelante': true si venía avanzando, false si venía retrocediendo.
void rampaDesaceleracion(int velInicialIzq, int velInicialDer, bool haciaAdelante) {
  int paso = 5; // Decremento de velocidad en cada paso
  int vMax = max(velInicialIzq, velInicialDer); // Tomar la velocidad más alta como referencia

  for (int v = vMax; v >= 0; v -= paso) {
    // Calcular velocidades proporcionales para cada motor en cada paso
    int currentVelIzq = map(v, 0, vMax, 0, velInicialIzq);
    int currentVelDer = map(v, 0, vMax, 0, velInicialDer);

    if (haciaAdelante) {
      adelante(currentVelIzq, currentVelDer);
    } else {
      atras(currentVelIzq, currentVelDer);
    }
    delay(25); // Pequeña pausa para una desaceleración más suave
  }
  detener(); // Asegura que los motores se detengan al final
}

// Controla los motores para avanzar
void adelante(int velIzq, int velDer) {
  digitalWrite(IN1, HIGH); // Motor izquierdo adelante
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, HIGH); // Motor derecho adelante
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velIzq); // Aplica velocidad PWM al motor izquierdo
  analogWrite(ENB, velDer); // Aplica velocidad PWM al motor derecho
}

// Controla los motores para retroceder
void atras(int velIzq, int velDer) {
  digitalWrite(IN1, LOW);  // Motor izquierdo atrás
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, LOW);  // Motor derecho atrás
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velIzq);
  analogWrite(ENB, velDer);
}

// Controla los motores para girar a la izquierda (ej: motor izq. atrás, motor der. adelante)
void girarIzquierda(int velIzq, int velDer) {
  digitalWrite(IN1, LOW);  // Izquierdo atrás
  digitalWrite(IN2, HIGH);
  digitalWrite(IN3, HIGH); // Derecho adelante
  digitalWrite(IN4, LOW);
  analogWrite(ENA, velIzq);
  analogWrite(ENB, velDer);
}

// Controla los motores para girar a la derecha (ej: motor izq. adelante, motor der. atrás)
void girarDerecha(int velIzq, int velDer) {
  digitalWrite(IN1, HIGH); // Izquierdo adelante
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);  // Derecho atrás
  digitalWrite(IN4, HIGH);
  analogWrite(ENA, velIzq);
  analogWrite(ENB, velDer);
}

// Detiene ambos motores por completo
void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENA, 0); // Establece velocidad a 0
  analogWrite(ENB, 0);
}


void setup() {
  pinMode(ENA, OUTPUT);
  pinMode(ENB, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  detener();
  delay(1500); // Espera X segundos al iniciar
}

void loop() {
  // --- Secuencia de Movimientos del Carrito ---

  // 1. Retroceder 1 metro
  rampaAceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, false); // Arranque suave atrás
  atras(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER); // Mantiene velocidad constante
  delay(TIEMPO_1M);
  rampaDesaceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, false); // Desaceleración suave

  detener();
  delay(200); // Pequeña pausa entre movimientos

  // 2. Giro a la izquierda 90°
  girarIzquierda(VEL_GIRO_IZQ, VEL_GIRO_DER); // Realiza el giro
  delay(TIEMPO_GIRO_90);
  detener();
  delay(200);

  // 3. Avanzar 0.5 metro
  rampaAceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, true); // Arranque suave adelante
  adelante(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER); // Mantiene velocidad constante
  delay(TIPO_05M);
  rampaDesaceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, true); // Desaceleración suave

  detener();
  delay(5000); // Espera 5 segundos antes del siguiente segmento

  // 4. Retroceder 0.5 metro
  rampaAceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, false); // Arranque suave atrás
  atras(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER); // Mantiene velocidad constante
  delay(TIPO_05M);
  rampaDesaceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, false); // Desaceleración suave

  detener();
  delay(200);

  // 5. Giro a la derecha 90°
  girarDerecha(VEL_GIRO_IZQ, VEL_GIRO_DER); // Realiza el giro
  delay(TIEMPO_GIRO_90);
  detener();
  delay(200);

  // 6. Avanzar 1 metro
  rampaAceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, true); // Arranque suave adelante
  adelante(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER); // Mantiene velocidad constante
  delay(TIEMPO_1M);
  rampaDesaceleracion(VELOCIDAD_BASE_IZQ, VELOCIDAD_BASE_DER, true); // Desaceleración suave

  detener();
  while (1); // Detiene la ejecución del loop indefinidamente al terminar el recorrido
             // Si quieres que se repita el recorrido, puedes comentar o eliminar esta línea.
}
