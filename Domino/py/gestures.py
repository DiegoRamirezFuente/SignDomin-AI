import cv2
import mediapipe as mp
import numpy as np
import time
from model_gestures import GestureClassifier
import sys

# Configuración de la cámara
camera_id = 0
video_height = 720
video_width = 720
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

filepath='communication.txt'
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
gesture_duration = 0  # Duración mínima para que un gesto sea válido
gesture_timestamp = time.time()  # Marca de tiempo cuando se detecta un gesto por primera vez
gestures_detected = []  # Lista para almacenar los gestos detectados por cada mano

# Bucle de captura de video y detección de gestos
while True:
    ret, frame = video.read()
    if not ret:
        break
    current_time = time.time()
    frame = cv2.cvtColor(frame, cv2.COLOR_BGR2RGB)
    frame.flags.writeable = False
    results = hands.process(frame)
    frame.flags.writeable = True
    frame = cv2.cvtColor(frame, cv2.COLOR_RGB2BGR)

    gesture = None  
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

    
    detected_gesture = get_gesture(gestures_detected, current_time, gesture_timestamp, gesture_duration)
    if detected_gesture is not None:
        #print(detected_gesture)
        send_message_to_cpp(detected_gesture, filepath)
        #time.sleep(0.1)
    # Mostrar el frame
    #cv2.imshow("JARI Video Capture", frame)

    # Control de salida con 'q'
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break

video.release()
cv2.destroyAllWindows()
