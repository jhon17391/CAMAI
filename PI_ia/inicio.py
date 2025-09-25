import torch
import serial
import time
import cv2

# Ruta de tu modelo entrenado
MODEL_PATH = "runs/detect/train/weights/best.pt"

# Inicializar serial con ESP32
ser = serial.Serial('/dev/ttyUSB0', 115200, timeout=1)
time.sleep(2)  # esperar que ESP32 inicialice

# Cargar modelo YOLOv5
model = torch.hub.load('ultralytics/yolov5', 'custom', path=MODEL_PATH, force_reload=True)

# Inicializar cámara
cap = cv2.VideoCapture(0)

# Función para enviar comandos al ESP32
def enviar_comando(servo_angle, motor_speed):
    msg = f"{servo_angle},{motor_speed}\n"
    ser.write(msg.encode())

while True:
    ret, frame = cap.read()
    if not ret:
        continue

    # Inferencia
    results = model(frame)

    # Procesar detecciones
    servo_angle = 90
    motor_speed = 200

    if results.xyxy[0].shape[0] > 0:  # si hay detecciones
        for *box, conf, cls in results.xyxy[0]:
            label = model.names[int(cls)]
            x_center = int((box[0]+box[2])/2)

            # Evitar pared
            if label == "wall":
                if x_center < frame.shape[1]//2:
                    servo_angle = 120  # girar a la derecha
                else:
                    servo_angle = 60   # girar a la izquierda

            # Esquivar cubo verde
            elif label == "green_cube":
                if x_center < frame.shape[1]//2:
                    servo_angle = 120
                else:
                    servo_angle = 60

            # Esquivar cubo rojo (opuesto al verde)
            elif label == "red_cube":
                if x_center < frame.shape[1]//2:
                    servo_angle = 60
                else:
                    servo_angle = 120

    # Enviar comando al ESP32
    enviar_comando(servo_angle, motor_speed)

    # Mostrar detecciones
    cv2.imshow("Detecciones", results.render()[0])
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

cap.release()
cv2.destroyAllWindows()
