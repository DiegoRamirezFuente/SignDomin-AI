import numpy as np
import tensorflow as tf
import os

class GestureClassifier(object):
    def __init__(
        self,
        model_path = os.path.join(os.path.dirname(__file__), 'model/gestures_classifier.tflite'),
        num_threads=1,
        confidence=0.9,
        smoothing_window_size=5
    ):
        # Cargar el modelo TFLite y preparar el intérprete
        self.interpreter = tf.lite.Interpreter(model_path=model_path)
        self.interpreter.allocate_tensors()
        self.input_details = self.interpreter.get_input_details()
        self.output_details = self.interpreter.get_output_details()
        self.confidence = confidence  # Umbral de confianza general para todos los gestos
        self.last_results = np.array([])  # Array para almacenar los últimos resultados y suavizar la salida
        self.smoothing_window_size = smoothing_window_size

    def __call__(self, landmark_list):
        # Procesar los landmarks y obtener una predicción del modelo
        input_details_tensor_index = self.input_details[0]['index']
        self.interpreter.set_tensor(input_details_tensor_index, np.array([landmark_list], dtype=np.float32))
        self.interpreter.invoke()
        output_details_tensor_index = self.output_details[0]['index']
        result = self.interpreter.get_tensor(output_details_tensor_index)
        result = np.squeeze(result)

        # Identificar el gesto con la máxima confianza
        result_index = np.argmax(result)
        if result[result_index] > self.confidence:  # Comprobar contra el umbral de confianza
            self.update_results(result_index)
        
        return result_index

    def update_results(self, new_result):
        # Actualizar el buffer de resultados para suavizar la predicción
        if len(self.last_results) >= self.smoothing_window_size:
            self.last_results = np.roll(self.last_results, -1)
            self.last_results[-1] = new_result
        else:
            self.last_results = np.append(self.last_results, new_result)