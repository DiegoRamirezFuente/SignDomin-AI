import numpy as np
import os
import time
import pickle 

# Parámetros para el Q-Learning
alpha = 0.1       # Tasa de aprendizaje
gamma = 0.9       # Factor de descuento
epsilon = 0.1     # Tasa de exploración 
num_actions = 15  # Número de acciones posibles 
state_size = 16   # Tamaño del estado de las fichas y del tablero

# Se comprueba si existe un tabla, si no, se crea
def load_q_table():
    if os.path.exists('q_table.pkl'):
        with open('q_table.pkl', 'rb') as f:
            return pickle.load(f)
    else:
        # Dimesiones: 7 fichas x 7 números. Estados posibles: 2^7. 15 acciones posibles
        return np.zeros((7, 7, 2**7, num_actions))

# Función responsable de guardar la tabla Q existente
def save_q_table():
    with open('q_table.pkl', 'wb') as f:
        pickle.dump(Q_table, f)

# Se crea o se carga la tabla Q
Q_table = load_q_table()

# Función que implementa el formato de estados a la tabla Q
def compact_state(state):
    left, right = state[0], state[1] # State[0] extremo izq del tablero. State[2] extremo der del tablero. 
    pieces = state[2:].reshape(-1, 2) # State[2] contiene las fichas. Se emparejan de 2 en 2
    # Se transforman las fichas a un número entero, que decodificado mostrará las fichas disponibles
    available_pieces = sum(2**i for i, piece in enumerate(pieces) if piece[0] != -1 and piece[1] != -1)
    return (left, right, available_pieces)


# Función responsable de seleccionar la acción utilizando epsilon-greedy
def select_action(state, epsilon):
    compact_current = compact_state(state)  
    if np.random.rand() < epsilon: # Si se supera la tasa de exploración, se explora
        # Se explora eligiendo una acción aleatoria
        return np.random.choice(num_actions)
    else:
        # Se explota, es decir, se elige la acción con el valor Q más alto 
        return np.argmax(Q_table[compact_current]) 

# Función para aplicar la acción y obtener recompensa
def apply_action(state, action):
    state = np.array(state) if not isinstance(state, np.ndarray) else state

    left = state[0]  
    right = state[1]  
    pieces = state[2:].reshape(-1, 2) 

    # Acción 0: se pasa el turno
    if action == 0:
        for piece in pieces:
            if left in piece or right in piece:
                return state, -1  # Se penaliza si se podía jugar ficha
        return state, 5  # Recompensa por pasar correctamente

    # Acciones 1 a 14: Colocar ficha
    piece_index = (action - 1) % 7  
    side = "left" if action <= 7 else "right"  
    selected_piece = pieces[piece_index]

    # Si la ficha no existe
    if selected_piece[0] == -1 and selected_piece[1] == -1:
        return state, -1  # Penalización

    # Validar jugada en el lado izquierdo
    if side == "left" and (selected_piece[0] == left or selected_piece[1] == left):
        new_left = selected_piece[1] if selected_piece[0] == left else selected_piece[0]
        new_state = state.copy()
        new_state[0] = new_left  # Actualizar extremo izquierdo
        new_state[2 + piece_index * 2:4 + piece_index * 2] = [-1, -1]  # Remover ficha
        return new_state, 5  # Recompensa positiva

    # Validar jugada en el lado derecho
    if side == "right" and (selected_piece[0] == right or selected_piece[1] == right):
        new_right = selected_piece[1] if selected_piece[0] == right else selected_piece[0]
        new_state = state.copy()
        new_state[1] = new_right  # Actualizar extremo derecho
        new_state[2 + piece_index * 2:4 + piece_index * 2] = [-1, -1]  # Remover ficha
        return new_state, 5  # Recompensa positiva

    # Penalización si la acción no es válida
    return state, -1

# Función para actualizar la tabla Q
def update_q_table(state, action, reward, next_state):
    compact_current = compact_state(state)
    compact_next = compact_state(next_state)
    max_next_q = np.max(Q_table[compact_next])  # Valor máximo en el siguiente estado
    Q_table[compact_current][action] += alpha * (reward + gamma * max_next_q - Q_table[compact_current][action])

# Ruta de los archivos
input_path = 'py/info.txt'
output_path = 'py/resultado.txt'

# Ciclo principal
while True:
    try:
        
        # Leer estado desde archivo
        if os.path.exists(input_path) and os.path.getsize(input_path) > 0:
            with open(input_path, 'r') as f:
                state = np.array([int(x) for x in f.read().strip().split(',')])

            print(f"Estado leído: {state}")

            # Seleccionar una acción
            action = select_action(state, epsilon)
            print(f"Acción seleccionada: {action}")

            # Aplicar la acción
            next_state, reward = apply_action(state, action)

            # Convertir next_state a NumPy array si no lo es
            if not isinstance(next_state, np.ndarray):
                next_state = np.array(next_state)

            print(f"Siguiente estado: {next_state}")
            print(f"Recompensa: {reward}")

            # Actualizar tabla Q
            update_q_table(state, action, reward, next_state)

            # Guardar la tabla Q después de actualizarla
            save_q_table()

            if reward > 0:
                # Escribir recompensa en resultado.txt
                with open(output_path, 'w') as f:
                    f.write(f"{action}")
                
                # Limpiar el contenido de info.txt
                with open(input_path, 'w') as f:
                    f.write("")
                
            
            #time.sleep(0.5)

    except Exception as e:
        print(f"Error: {e}")
        break
