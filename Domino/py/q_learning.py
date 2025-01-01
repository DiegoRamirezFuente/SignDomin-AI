import numpy as np
import os
import pickle
import time

# Parámetros para el Q-Learning
alpha = 0.1       # Tasa de aprendizaje
gamma = 0.9       # Factor de descuento
epsilon = 0.1     # Tasa de exploración
num_actions = 15  # Número de acciones posibles
state_size = 16   # Tamaño del estado 

OPTIMAL_REWARD = 10  # Recompensa usada al procesar la jugada del jugador local
BASE_REWARD = 1      # Recompensa base para acciones legales

#Rutas de los ficheros de comunicación
player_input_path = 'py/communication_files/Jugador.txt'
input_path = 'py/communication_files/info.txt'
output_path = 'py/communication_files/resultado.txt'
exit_flag_path = 'py/communication_files/exit_flag.txt'
# Se carga o se inicializa la tabla Q 
def load_q_table():
    if os.path.exists('py/q_table.pkl'):
        with open('py/q_table.pkl', 'rb') as f:
            return pickle.load(f)
    else:
        return np.zeros((7, 7, 2**7, num_actions))

# Se guarda la tabla Q
def save_q_table(Q_table):
    with open('py/q_table.pkl', 'wb') as f:
        pickle.dump(Q_table, f)

# Instancia de la tabla Q
Q_table = load_q_table()

# Función necesaria para compactar en binario el estado en la tabla
def compact_state(state):
    left, right = state[0], state[1]
    # Se almacenan las fichas 
    pieces = state[2:].reshape(-1, 2)
    
    available_mask = 0
    for i, piece in enumerate(pieces):
        # Transformación para cuando la ficha vale -1 (no disponible)
        if piece[0] != -1 and piece[1] != -1:
            available_mask |= (1 << i)
            
    return (left, right, available_mask)

#Función para actualizar la tabla Q 
def update_q_table(Q_table, state, action, reward, next_state):
    compact_current = compact_state(state)
    compact_next = compact_state(next_state)
    max_next_q = np.max(Q_table[compact_next])
    #Fórmula de Q(s,a)
    Q_table[compact_current][action] += alpha * (
        reward + gamma * max_next_q - Q_table[compact_current][action]
    )


#Función que determina si la acción es legal
def get_legal_actions(state):
    left, right = state[0], state[1]
    pieces = state[2:].reshape(-1, 2)
    legal_actions = []
    
    # Se comprueba cada ficha
    for i in range(7):
        p = pieces[i]
        if p[0] == -1 and p[1] == -1:
            # Ficha ya usada
            continue
        # Poner a la izquierda
        if p[0] == left or p[1] == left:
            legal_actions.append(i + 1) 
        # Poner a la derecha
        if p[0] == right or p[1] == right:
            legal_actions.append(i + 8)  
    
    #Si no hay acciones legales, accion=0 (se pasa)
    if len(legal_actions) == 0:
        legal_actions = [0]
    #Devuelve la lista de las acciones legales 
    return legal_actions

#Función que evalua el posible bonus obtenido por cada acción legal
def evaluate_actions(state, possible_actions, base_reward=BASE_REWARD):
    scores = {}
    left = state[0]
    right = state[1]
    pieces = state[2:].reshape(-1, 2)

    for action in possible_actions:
        #No hay bonus por pasar
        if action == 0:
            scores[action] = 0
            continue
        
        piece_index = (action - 1) % 7
        selected_piece = pieces[piece_index]
        
        #Ficha doble = 5
        bonus_doble = 0
        if selected_piece[0] == selected_piece[1]:
            bonus_doble = 5
        
        #Se simula el estado futuro tras poner la nueva ficha
        new_left, new_right = future_state(left, right, selected_piece, action)
        #Se comprueban las compatibilidades futuras de jugar una ficha
        #Bonus=numero de fichas compatibles
        compat_futura = compatible_pieces(new_left, new_right, pieces, piece_index)
   
        score = base_reward + bonus_doble + compat_futura
        
        scores[action] = score
    #Se devuelve la recompensa total
    return scores

#Función utilizada para calcular el bonus, predice el estado futuro tras poner una ficha
def future_state(left, right, piece, action):
    side = "left" if action <= 7 else "right"
    new_left = left
    new_right = right

    if side == "left":
        if piece[0] == left:
            new_left = piece[1]
        else:
            new_left = piece[0]
    else:
        if piece[0] == right:
            new_right = piece[1]
        else:
            new_right = piece[0]
    
    return new_left, new_right

#Función que cuenta el número de fichas compatibles
def compatible_pieces(new_left, new_right, pieces, used_index):
    count = 0
    for i, p in enumerate(pieces):
        if i == used_index:
            continue
        if p[0] != -1 and p[1] != -1:
            if new_left in p or new_right in p:
                count += 1
    return count

#Función que devuelve el nuevo estado tras aplicar una acción legal
def new_state(state, action):
    new_state = state.copy()
    pieces = new_state[2:].reshape(-1, 2)
    
    #Al pasar no se modifica nada
    if action == 0:
        return new_state
    
    left = new_state[0]
    right = new_state[1]
    piece_index = (action - 1) % 7
    side = "left" if action <= 7 else "right"
    selected_piece = pieces[piece_index]

    #Se actualiza el tablero
    if side == "left":
        if selected_piece[0] == left:
            new_state[0] = selected_piece[1]
        else:
            new_state[0] = selected_piece[0]
    else:
        if selected_piece[0] == right:
            new_state[1] = selected_piece[1]
        else:
            new_state[1] = selected_piece[0]
    
    new_state[2 + piece_index*2] = -1
    new_state[2 + piece_index*2 + 1] = -1
    
    return new_state

#Función para aplicar la acción escogida. 
def apply_action(state, action):
    possible_actions = get_legal_actions(state)
    
    if len(possible_actions) == 1 and possible_actions[0] == 0:
        # Si el agente pasa siendo la única acción posible, Reward = 5
        if action == 0:
            return state, 5
        else:
            return state, -1
    
    if action not in possible_actions:
        #Si la jugada es ilegal
        return state, -1
    
    #Se obtiene la recompensa por la acción legal
    scores = evaluate_actions(state, possible_actions)
    reward = scores[action]
    
    #Se construye el siguiente estado
    next_state = new_state(state, action)
    
    return next_state, reward

#Función para procesar en la tabla los movimientos del jugador local 
def player_action(Q_table):
    if os.path.exists(player_input_path) and os.path.getsize(player_input_path) > 0:
        with open(player_input_path, 'r') as f:
            data = f.read().strip().split(',')
    
        if len(data) != 17:
            print(f"Error en 'Jugador.txt': {data}")
            return
        
        action = int(data[0])
        state = np.array([int(x) for x in data[1:]])
        
        print(f"Jugada óptima del jugador: Acción {action}, Estado {state}")
        
        # Aplicar la acción al estado
        next_state, _ = apply_action(state, action)
        
        # Actualizar Q con recompensa óptima
        update_q_table(Q_table, state, action, OPTIMAL_REWARD, next_state)
        print("Tabla Q actualizada con la jugada del jugador.")
        
        # Limpiar el archivo tras procesar
        with open(player_input_path, 'w') as f:
            f.write("")

#Política Epsilon-Greedy
def policy(state, Q_table, epsilon):
    compact_current = compact_state(state)
    left, right, available_mask = compact_current
    #Exploración
    if left < 0 or left > 6 or right < 0 or right > 6:
        print(f"Extremos no válidos: left={left}, right={right}")
        return 0  
    
    if available_mask < 0 or available_mask >= 2**7:
        print(f"Máscaras inválidas: available_mask={available_mask}")
        return 0 
    if np.random.rand() < epsilon:
        state_index = (left, right, available_mask)
        legal_actions = get_legal_actions(state)
        action = np.random.choice(legal_actions)
        return action
    else:
        #Explotación
        state_index = (left, right, available_mask)
        return np.argmax(Q_table[state_index])
    
def clear_file(filepath):
    # Vacía el contenido del archivo
    with open(filepath, 'w') as f:
        f.truncate()
        
# Función principal del programa. Realiza un bucle infinito
def main():
    global Q_table
    while True:
        try:
            #Se procesa la jugada del jugador, si existe
            player_action(Q_table)
            if os.path.exists(exit_flag_path) and os.path.getsize(exit_flag_path) > 0:
                flag=np.loadtxt(exit_flag_path)
                if flag == 1:
                    clear_file(exit_flag_path)
                    exit(1)
            #Se lee el archivo del estado
            if os.path.exists(input_path) and os.path.getsize(input_path) > 0:
                with open(input_path, 'r') as f:
                    data = f.read().strip().split(',')
                
                if len(data) != 16:
                    print(f"Estado no válido: {data}")
                    continue
                
                state = np.array([int(x) for x in data])
                #Se aplica una acción y se calcula la recompensa
                print(f"Estado leído: {state}")
                action = policy(state, Q_table, epsilon)
                print(f"Acción seleccionada: {action}")
                next_state, reward = apply_action(state, action)
                print(f"Siguiente estado: {next_state}")
                print(f"Recompensa: {reward}")

                #Se actualiza la tabla Q
                update_q_table(Q_table, state, action, reward, next_state)
                
                #Se almacena la tabla Q
                save_q_table(Q_table)

                #Si la acción es válida, se escribe en el archivo de salida
                if reward >= BASE_REWARD:
                    with open(output_path, 'w') as f:
                        f.write(f"{action}")
                    #Se limpia el archivo de entrada
                    with open(input_path, 'w') as f:
                        f.write("")
                #Delay para simular el "pensamiento del agente"
                time.sleep(0.5)

        except Exception as e:
            print(f"Error: {e}")
            break

if __name__ == "__main__":
    main()
