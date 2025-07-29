#include <Servo.h>

// --------------------- Pines y configuración ----------------------

const int ENB = 6;   // PWM de velocidad motor trasero
const int IN3 = 7;   // Dirección motor trasero
const int IN4 = 8;

const int pinServo = 9;  // Pin del servo de dirección
const int SERVO_CENTRO = 96; // Ángulo central del servo
const int SERVO_IZQUIERDA = 110; // Ángulo para girar izquierda
const int SERVO_DERECHA = 86;    // Ángulo para girar derecha

const int VELOCIDAD = 190; // Velocidad del motor trasero (0–255)

Servo direccion;

void setup() {
  // Configuración de pines
  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  direccion.attach(pinServo); // Inicializar servo
  centrarDireccion();         // Posición inicial
  delay(1000);                // Pausa de arranque
}

void loop() {
  //delay de inicio
  delay(2000);

  // centrar direccion
  centrarDireccion();
  delay(500);

  // Girar a la izquierda
  girarIzquierda();
  delay(500);
  //avanzar
  avanzar();
  delay(43000);

  centrarDireccion();
  detener();
  delay(20000);

}
