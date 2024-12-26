import numpy as np
import time
from model_domino import DominoIA
import os

dominoIA = DominoIA();
input_path = 'py/info.txt'  
output_path = 'py/resultado.txt' 
exit_flag_path = 'py/exit_flag.txt'

def normalize_data(data):
    normalized_data = np.where(
        data == -1,      # Si el valor es -1 (sin ficha)
        0,               # Mapearlo a 0
        (data + 1) / 7   # Escalar los valores [0, 6] a [0.1, 1]
    )
    return normalized_data

def load_and_normalize_data(file_path):
    data = np.loadtxt(file_path, delimiter=',')
    x_data_normalized = np.array([normalize_data(x) for x in data])
    return x_data_normalized

def send_message_to_cpp(message, filepath):
    with open(filepath, 'w') as f:
        f.write(str(message))
        
def clear_file(filepath):
    # Vacía el contenido del archivo
    with open(filepath, 'w') as f:
        f.truncate()
print("ANN") 
while True:
    try:
        
       if os.path.exists(exit_flag_path) and os.path.getsize(exit_flag_path) > 0:
           flag=np.loadtxt(exit_flag_path)
           if flag == 1:
               clear_file(exit_flag_path)
               exit(1)
               
       if os.path.exists(input_path) and os.path.getsize(input_path) > 0:
            x_normalized = load_and_normalize_data(input_path)
            model_output = dominoIA(x_normalized)
            print(model_output)
            send_message_to_cpp(model_output, output_path)
            clear_file(input_path)
            time.sleep(1)
            
        
        
    except Exception as e:
        print(f"Error al leer el archivo: {e}")
        time.sleep(1)  