import cv2
import mediapipe as mp
import numpy as np
import time
from model_gestures import GestureClassifier
import sys
import os
# Configuración de la cámara
camera_id = 0
video_height = 300
video_width = 300
video = cv2.VideoCapture(camera_id)
video.set(cv2.CAP_PROP_FRAME_HEIGHT, video_height)
video.set(cv2.CAP_PROP_FRAME_WIDTH, video_width)

# Configuración de la herramienta Hands de Mediapipe
mp_hands = mp.solutions.hands
hands = mp_hands.Hands(min_detection_confidence=0.5, min_tracking_confidence=0.5)
mp_drawing = mp.solutions.drawing_utils

# Objeto del modelo clasificador de gestos
gesture_classifier = GestureClassifier()

# Diccionario de gestos
gestures_dict = {
    0: 'fist',
    1: 'one',
    2: 'two',
    3: 'three',
    4: 'four',
    5: 'five',
    6: 'left',
    7: 'right'
}

filepath='py/communication_files/communication.txt'
exit_flag_path = 'py/communication_files/exit_flag.txt'
def send_message_to_cpp(message, filepath):
    with open(filepath, 'w') as f:
        f.write(str(message))
        
def process_landmarks(image, landmarks):
    image_width, image_height = image.shape[1], image.shape[0]
    raw_landmark_list = []

    for _, landmark in enumerate(landmarks.landmark):
        landmark_x = min(int(landmark.x * image_width), image_width - 1)
        landmark_y = min(int(landmark.y * image_height), image_height - 1)
        raw_landmark_list.append([landmark_x, landmark_y])

    ref_landmark = np.array(raw_landmark_list[0])
    rel_landmark_list = np.array(raw_landmark_list) - ref_landmark
    aux_landmark_list = np.array(rel_landmark_list)
    one_d_landmark_list = aux_landmark_list.flatten()
    max_value = np.max(np.abs(one_d_landmark_list))
    normalized_landmark_list = one_d_landmark_list / max_value

    return normalized_landmark_list

def clear_file(filepath):
    # Vacía el contenido del archivo
    with open(filepath, 'w') as f:
        f.truncate()
        
def get_gesture(gestures_detected, current_time, gesture_timestamp, gesture_duration):
    gesture = None
    if (len(gestures_detected) == 2 and gestures_detected[0] == 1 and gestures_detected[1] == 5) or (len(gestures_detected) == 2 and gestures_detected[0] == 5 and gestures_detected[1] == 1):
        gesture = sum(gestures_detected) + 2  
        return gesture
    if (len(gestures_detected) == 2 and gestures_detected[0] == 2 and gestures_detected[1] == 5) or (len(gestures_detected) == 2 and gestures_detected[0] == 5 and gestures_detected[1] == 2):
        gesture = sum(gestures_detected) + 2  
        return gesture
    elif len(gestures_detected) == 1:  
        gesture = gestures_detected[0]  
    if gesture is not None and current_time - gesture_timestamp >= gesture_duration:
        return gesture
    else:
        return None  
    
# Inicialización de variables
last_gesture = None
gesture_display = None
start_time = None
last_update_time = time.time()
gesture_duration = 0.5  # Duración mínima para que un gesto sea válido
gesture_timestamp = time.time()  # Marca de tiempo cuando se detecta un gesto por primera vez
gestures_detected = []  # Lista para almacenar los gestos detectados por cada mano
stable_gesture = None  # Gesto estable que ha cumplido el tiempo
stable_gesture_time = 0  # Marca de tiempo inicializada como 0

# Bucle de captura de video y detección de gestos
while True:
    
    if os.path.exists(exit_flag_path) and os.path.getsize(exit_flag_path) > 0:
        flag=np.loadtxt(exit_flag_path)
        if flag == 0:
            clear_file(exit_flag_path)
            exit(1)
            
    ret, frame = video.read()
    if not ret:
        break
    current_time = time.time()
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    frame.flags.writeable = False
    results = hands.process(frame)
    frame.flags.writeable = True
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    gestures_detected.clear() 

    if results.multi_hand_landmarks:
        for hand_landmarks in results.multi_hand_landmarks:
            mp_drawing.draw_landmarks(frame, hand_landmarks, mp_hands.HAND_CONNECTIONS)
            landmarks = process_landmarks(frame, hand_landmarks)
            gesture_index = gesture_classifier(landmarks)

            gestures_detected.append(gesture_index)

            if gesture_index != last_gesture:
                last_gesture = gesture_index
                gesture_timestamp = current_time

    # Verificar gesto detectado
    detected_gesture = get_gesture(gestures_detected, current_time, gesture_timestamp, gesture_duration)

    # Validar si el gesto se mantiene estable
    if detected_gesture is not None:
        if stable_gesture is None or stable_gesture != detected_gesture:
            # Iniciar el temporizador para el nuevo gesto
            stable_gesture = detected_gesture
            stable_gesture_time = current_time
        elif current_time - stable_gesture_time >= gesture_duration:
            # El gesto es válido después de 0.7 segundos
            #print(stable_gesture)
            send_message_to_cpp(stable_gesture, filepath);
            stable_gesture = None  # Reiniciar para evitar impresiones repetidas
            stable_gesture_time = 0  # Resetear el tiempo
    else:
        # Reiniciar el gesto estable si no hay un gesto detectado
        stable_gesture = None
        stable_gesture_time = 0

    # Mostrar el frame
    #cv2.imshow("Camera Frame", frame)

    # Control de salida con 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video.release()
cv2.destroyAllWindows()
