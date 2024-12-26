#pragma once
#include "Tablero.h"
#include "GestureReader.h"
#include <sys/stat.h>
#include <thread>   // Para sleep_for
#include <chrono>   // Para chrono literals
#include <windows.h>
#include <string>
#include <iostream>

class Coordinador {
private:
	int modo;
	int dificultad; // Para elegir entre Fácil, Intermedio o Difícil
	Tablero tablero; // El tablero, el cual controla todo el transcurso de la partida
	enum Estado { LOADING0, LOADING1, LOADING2, MENU, INSTRUCCIONES, OPCIONES, JUEGO };
	Estado estado;
	GestureReader gesto; // Para controlar los gestos realizados
	int bucle = 0;
public:
	Coordinador();
	~Coordinador();
	int mode=-1;
	int get_Modo() { return modo; }
	void runANN();
	void runQlearning();

	// FUNCIONES RELACIONADAS CON EL CONTROL DE LAS ELECCIONES DEL USUARIO
	void control_Raton(int x, int y);
	void control_Gestos();
	void escribirExitFlag();
	// FUNCIÓN RELACIONADA CON EL MOVIMIENTO DE LAS PIEZAS EN EL TABLERO
	void partida();

	// FUNCIONES RELACIONADAS CON EL MODO GRÁFICO
	void dibuja();
	void dibuja_Menu();
};