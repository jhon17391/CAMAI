void avanzar() {
  digitalWrite(IN4, HIGH);
  digitalWrite(IN3, LOW);
  analogWrite(ENB, 180);
}

void detener() {
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
  analogWrite(ENB, 0);
}

void centrarDireccion() {
  direccion.write(SERVO_CENTRO);
}

void girarIzquierda() {
  direccion.write(SERVO_IZQUIERDA);
}

void girarDerecha() {
  direccion.write(SERVO_DERECHA);
}
