import numpy as np
import os
import pickle
import time

# Parámetros para el Q-Learning
alpha = 0.1       # Tasa de aprendizaje
gamma = 0.9       # Factor de descuento
epsilon = 0.1     # Tasa de exploración
num_actions = 15  # Número de acciones posibles
state_size = 16   # Tamaño del estado de las fichas y del tablero

# Recompensa máxima que representa una jugada óptima
OPTIMAL_REWARD = 10

# Se carga la tabla Q o se inicializa
def load_q_table():
    if os.path.exists('q_table.pkl'):
        with open('q_table.pkl', 'rb') as f:
            return pickle.load(f)
    else:
        return np.zeros((7, 7, 2**7, num_actions))

# Guardar tabla Q
def save_q_table():
    with open('q_table.pkl', 'wb') as f:
        pickle.dump(Q_table, f)

Q_table = load_q_table()

# Convertir estado al formato de tabla Q
def compact_state(state):
    left, right = state[0], state[1]
    pieces = state[2:].reshape(-1, 2)
    available_pieces = sum(2**i for i, piece in enumerate(pieces) if piece[0] != -1 and piece[1] != -1)
    return (left, right, available_pieces)

# Actualizar tabla Q con un estado, acción, recompensa y siguiente estado
def update_q_table(state, action, reward, next_state):
    compact_current = compact_state(state)
    compact_next = compact_state(next_state)
    max_next_q = np.max(Q_table[compact_next])
    Q_table[compact_current][action] += alpha * (reward + gamma * max_next_q - Q_table[compact_current][action])

# Ruta de archivos
player_input_path = 'Jugador.txt'
input_path = 'py/info.txt'
output_path = 'py/resultado.txt'

# Procesar jugadas óptimas del jugador
def process_player_move():
    if os.path.exists(player_input_path) and os.path.getsize(player_input_path) > 0:
        with open(player_input_path, 'r') as f:
            data = f.read().strip().split(',')
        
        # Parsear el formato: <acción>,<tablero izquierdo>,<tablero derecho>,<números de fichas>
        action = int(data[0])
        state = np.array([int(x) for x in data[1:]])

        print(f"Jugada óptima del jugador: Acción {action}, Estado {state}")

        # Aplicar la acción al estado
        next_state, _ = apply_action(state, action)

        # Actualizar tabla Q con recompensa máxima
        update_q_table(state, action, OPTIMAL_REWARD, next_state)
        print("Tabla Q actualizada con la jugada del jugador.")

        # Limpiar archivo del jugador después de procesar
        with open(player_input_path, 'w') as f:
            f.write("")

# Seleccionar acción para el bot usando epsilon-greedy
def select_action(state, epsilon):
    compact_current = compact_state(state)
    if np.random.rand() < epsilon:
        return np.random.choice(num_actions)  # Explorar
    else:
        return np.argmax(Q_table[compact_current])  # Explotar

# Aplicar acción y calcular recompensa
def apply_action(state, action):
    state = np.array(state) if not isinstance(state, np.ndarray) else state
    left = state[0]
    right = state[1]
    pieces = state[2:].reshape(-1, 2)

    if action == 0:  # Pasar
        for piece in pieces:
            if left in piece or right in piece:
                return state, -1
        return state, 5

    piece_index = (action - 1) % 7
    side = "left" if action <= 7 else "right"
    selected_piece = pieces[piece_index]

    if selected_piece[0] == -1 and selected_piece[1] == -1:
        return state, -1

    if side == "left" and (selected_piece[0] == left or selected_piece[1] == left):
        new_left = selected_piece[1] if selected_piece[0] == left else selected_piece[0]
        new_state = state.copy()
        new_state[0] = new_left
        new_state[2 + piece_index * 2:4 + piece_index * 2] = [-1, -1]
        return new_state, 5

    if side == "right" and (selected_piece[0] == right or selected_piece[1] == right):
        new_right = selected_piece[1] if selected_piece[0] == right else selected_piece[0]
        new_state = state.copy()
        new_state[1] = new_right
        new_state[2 + piece_index * 2:4 + piece_index * 2] = [-1, -1]
        return new_state, 5

    return state, -1

# Ciclo principal
while True:
    try:
        process_player_move()  # Procesa jugada del jugador si existe

        if os.path.exists(input_path) and os.path.getsize(input_path) > 0:
            with open(input_path, 'r') as f:
                state = np.array([int(x) for x in f.read().strip().split(',')])

            print(f"Estado leído: {state}")
            action = select_action(state, epsilon)
            print(f"Acción seleccionada: {action}")
            next_state, reward = apply_action(state, action)
            print(f"Siguiente estado: {next_state}")
            print(f"Recompensa: {reward}")

            update_q_table(state, action, reward, next_state)
            save_q_table()

            if reward > 0:
                with open(output_path, 'w') as f:
                    f.write(f"{action}")
                with open(input_path, 'w') as f:
                    f.write("")
            
            time.sleep(0.5)
    except Exception as e:
        print(f"Error: {e}")
        break
