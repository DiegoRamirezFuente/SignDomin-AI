#pragma once
#include "Tablero.h"
#include <iostream>
#include <fstream>
#include <string>

class Coordinador {
private:
	int dificultad; // Para elegir entre Fácil, Intermedio o Difícil
	Tablero tablero; // El tablero, el cual controla todo el transcurso de la partida
	enum Estado {MENU, INSTRUCCIONES, JUEGO};
	Estado estado;

	// Crear y abrir el archivo CSV
	//ofstream archivo;
public:
	Coordinador();
	~Coordinador();

	// FUNCIONES RELACIONADAS CON EL MENU
	void control_Raton(int x, int y);

	// para controlar el desarrollo de la partida
	void partida();

	// FUNCIONES RELACIONADAS CON EL MODO GRÁFICO
	void dibuja();
	void dibuja_Menu();
	void dibuja_Instrucciones();


};