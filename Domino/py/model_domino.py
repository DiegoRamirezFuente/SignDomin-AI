import numpy as np
import tensorflow as tf
import os

class DominoIA(object):
    def __init__(self, model_path=None, confidence=0.1):
        if model_path is None:
            model_path = os.path.join(os.path.dirname(__file__), 'model/domino_classifier.tflite')
    
        self.interpreter = tf.lite.Interpreter(model_path=model_path)
        self.interpreter.allocate_tensors()
        self.input_details = self.interpreter.get_input_details()
        self.output_details = self.interpreter.get_output_details()
        self.confidence = confidence  

    def __call__(self, data_list):
        input_details_tensor_index = self.input_details[0]['index']
        self.interpreter.set_tensor(input_details_tensor_index, np.array([data_list], dtype=np.float32))
        self.interpreter.invoke()
        output_details_tensor_index = self.output_details[0]['index']
        result = self.interpreter.get_tensor(output_details_tensor_index)
        result = np.squeeze(result)

        result_index = np.argmax(result)
        if result[result_index] > self.confidence:  
            return result_index
        else:
            return -1 

