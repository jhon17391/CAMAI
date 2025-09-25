#include <Arduino.h>
#include <Servo.h>

// Pines del L298N (ajusta según tu conexión)
const int ENA = 25;   // PWM velocidad motor
const int IN1 = 26;   // Dirección motor
const int IN2 = 27;

// Servo de dirección
Servo direccionServo;
const int SERVO_PIN = 14;

// Velocidad base del motor (0-255)
int velocidad = 200;

void setup() {
  Serial.begin(115200);

  // Pines motor
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  // Servo
  direccionServo.attach(SERVO_PIN);
  direccionServo.write(90); // Centrado al inicio

  detener();
  Serial.println("ESP32 lista para recibir comandos...");
}

void loop() {
  if (Serial.available()) {
    String comando = Serial.readStringUntil('\n');
    comando.trim();

    if (comando == "ADELANTE") {
      adelante();
    } else if (comando == "ATRAS") {
      atras();
    } else if (comando == "IZQUIERDA") {
      izquierda();
    } else if (comando == "DERECHA") {
      derecha();
    } else if (comando == "DETENER") {
      detener();
    } else {
      Serial.println("Comando no reconocido: " + comando);
    }
  }
}

// Funciones de control
void adelante() {
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, velocidad);
  direccionServo.write(90); // recto
  Serial.println("Moviendo hacia adelante");
}

void atras() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  analogWrite(ENA, velocidad);
  direccionServo.write(90);
  Serial.println("Moviendo hacia atras");
}

void izquierda() {
  direccionServo.write(60); // ajusta según tu mecánica
  Serial.println("Girando a la izquierda");
}

void derecha() {
  direccionServo.write(120); // ajusta según tu mecánica
  Serial.println("Girando a la derecha");
}

void detener() {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  analogWrite(ENA, 0);
  direccionServo.write(90); // recto
  Serial.println("Robot detenido");
}
