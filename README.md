# SignDomin-AI
- __INTRODUCCIÓN.__

SignDomin-AI es un simulador de dominó, programado en C++ y Python, que combina técnias de inteligencia artificial con una experiencia de usuario basada en gestos. Diseñado para ofrecer tanto diversión como un desafío estratégico, este proyecto es ideal para quienes disfrutan del dominó y están interesados en cómo la IA puede transformar los juegos clásicos. El simulador cuenta con una interacción intuitiva mediante gestos y agentes inteligentes que garantizan partidas dinámicas y emocionantes.

![loading1](https://github.com/user-attachments/assets/84a15e3a-1cc4-433f-9bd4-43c47edbd77a)

- __RECONOCIMIENTO DE GESTOS.__

Una de las características principales de SignDomin-AI es su capacidad para reconocer gestos en tiempo real. Usando redes neuronales artificiales (ANN) y el framework Mediapipe, el sistema interpreta las acciones del jugador, permitiendo controlar las fichas de manera intuitiva y sin necesidad de dispositivos adicionales. Esto no solo facilita la experiencia de juego, sino que también proporciona una interfaz accesible para todos los usuarios.

![2025-01-01 20-54-38 (1)](https://github.com/user-attachments/assets/e5b21645-ec63-4420-ae3b-a3fefd154377)

- __AGENTES INTELIGENTES.__

En SignDomin-AI, los jugadores rivales utilizan diferentes enfoques de inteligencia artificial:

  - __Agente basado en ANN:__ Este agente emplea redes neuronales artificiales para analizar el tablero y tomar decisiones estratégicas. Su comportamiento está diseñado para simular un jugador humano.
  
  - __Agente basado en RL:__ Este agente utiliza aprendizaje por refuerzo para adaptarse y aprender durante la partida. Su estrategia evoluciona a medida que juega, ofreciendo un desafío dinámico y único en cada enfrentamiento.

![2025-01-01 21-27-07 (1)](https://github.com/user-attachments/assets/2cdd2e5a-b04e-481b-9c0f-a1a965e84fea)

__INSTRUCCIONES DE INSTALACIÓN.__

1. INSTALAR https://www.python.org/ftp/python/3.8.8/python-3.8.8-amd64.exe
   **IMPORTANTE AÑADIR AL PATH DURANTE LA INSTALACIÓN**
2. IR AL CMD Y EJECUTAR:
   
   python -m pip install mediapipe
   
   python -m pip install opencv-python
   
   python -m pip install tensorflow==2.13
