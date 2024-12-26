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

# Verificar si existe la tabla Q o crearla
def load_q_table():
    if os.path.exists('q_table.pkl'):
        with open('q_table.pkl', 'rb') as f:
            return pickle.load(f)
    else:
        # Crear tabla Q inicializada a ceros
        return np.zeros((7, 7, 2**7, num_actions))

# Guardar la tabla Q
def save_q_table():
    with open('q_table.pkl', 'wb') as f:
        pickle.dump(Q_table, f)

# Cargar o inicializar tabla Q
Q_table = load_q_table()

# Función que transforma el estado en una representación compacta para la tabla Q
def compact_state(state):
    left, right = state[0], state[1]  # Extremos izquierdo y derecho del tablero
    pieces = state[2:].reshape(-1, 2)  # Fichas disponibles en pares
    # Codificar las fichas disponibles como un entero
    available_pieces = sum(2**i for i, piece in enumerate(pieces) if piece[0] != -1 and piece[1] != -1)
    return (left, right, available_pieces)

# Función para evaluar fichas y asignarles una puntuación
def evaluate_piece(piece, side, left, right):
    """
    Calcula el valor de una ficha basada en:
    - Su valor numérico.
    - Si es jugable (en el lado izquierdo o derecho).
    """
    if side == "left" and (piece[0] == left or piece[1] == left):
        return piece[0] + piece[1]  # Sumar los valores como una métrica básica
    elif side == "right" and (piece[0] == right or piece[1] == right):
        return piece[0] + piece[1]
    return -1  # No jugable en este lado

# Función para aplicar la acción y validar si es realizable
def is_action_valid(state, action):
    state = np.array(state) if not isinstance(state, np.ndarray) else state

    left = state[0]  
    right = state[1]  
    pieces = state[2:].reshape(-1, 2)  # Fichas del jugador en pares

    # Acción 0: Pasar turno (si no hay fichas jugables, es válida)
    if action == 0:
        for piece in pieces:
            if left in piece or right in piece:
                return False  # No válida si se podía jugar ficha
        return True  # Válida si no se puede jugar ninguna ficha

    # Acciones 1 a 14: Colocar ficha
    piece_index = (action - 1) % 7  # Índice de la ficha seleccionada
    side = "left" if action <= 7 else "right"  # Lado donde jugar
    selected_piece = pieces[piece_index]

    # Si la ficha no existe
    if selected_piece[0] == -1 and selected_piece[1] == -1:
        return False  # No válida por ficha inválida

    # Validar jugada en el lado correspondiente
    if side == "left" and (selected_piece[0] == left or selected_piece[1] == left):
        return True  # Válida si se puede jugar en el lado izquierdo

    if side == "right" and (selected_piece[0] == right or selected_piece[1] == right):
        return True  # Válida si se puede jugar en el lado derecho

    # No válida si no cumple ninguna de las condiciones
    return False

# Función para seleccionar acción con evaluación de fichas
def select_action(state, epsilon):
    compact_current = compact_state(state)  # Compactar el estado actual
    if np.random.rand() < epsilon:  # Exploración
        return np.random.choice(num_actions)

    # Explotación: Seleccionar la mejor ficha disponible
    best_action = 0
    best_score = -float('inf')

    left, right = state[0], state[1]
    pieces = state[2:].reshape(-1, 2)

    for i, piece in enumerate(pieces):
        if piece[0] == -1 and piece[1] == -1:
            continue  # Ficha no disponible
        # Evaluar jugabilidad en ambos lados
        score_left = evaluate_piece(piece, "left", left, right)
        score_right = evaluate_piece(piece, "right", left, right)
        # Actualizar mejor jugada encontrada
        if score_left > best_score:
            best_score = score_left
            best_action = i + 1  # Acción para colocar en el lado izquierdo
        if score_right > best_score:
            best_score = score_right
            best_action = i + 8  # Acción para colocar en el lado derecho

    return best_action if best_score > -1 else 0  # Si no hay jugadas, pasar turno

# Archivos para lectura/escritura de estados
input_path = 'info.txt'
output_path = 'resultado.txt'

# Ciclo principal para lectura/escritura de acciones
while True:
    try:
        # Leer estado desde el archivo
        if os.path.exists(input_path) and os.path.getsize(input_path) > 0:
            with open(input_path, 'r') as f:
                state = np.array([int(x) for x in f.read().strip().split(',')])

            print(f"Estado leído: {state}")

            # Seleccionar una acción
            action = select_action(state, epsilon)
            print(f"Acción tentativa: {action}")

            # Validar la acción
            if is_action_valid(state, action):
                print(f"Acción válida: {action}")
                # Escribir la acción en el archivo de salida
                with open(output_path, 'w') as f:
                    f.write(str(action))
            else:
                print(f"Acción {action} no válida. Esperando estado válido.")

            # Guardar tabla Q
            save_q_table()

            # Simulación de tiempo
            time.sleep(0.1)

    except Exception as e:
        print(f"Error: {e}")
        break
