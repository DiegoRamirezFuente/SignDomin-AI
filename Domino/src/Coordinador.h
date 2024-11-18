#pragma once
#include "Tablero.h"
#include "GestureReader.h"

class Coordinador {
private:
	int modo;
	int dificultad; // Para elegir entre F�cil, Intermedio o Dif�cil
	Tablero tablero; // El tablero, el cual controla todo el transcurso de la partida
	enum Estado { MENU, INSTRUCCIONES, OPCIONES, JUEGO };
	Estado estado;
	GestureReader gesto; // Para controlar los gestos realizados
public:
	Coordinador();
	~Coordinador();
	int get_Modo() { return modo; }

	// FUNCIONES RELACIONADAS CON EL CONTROL DE LAS ELECCIONES DEL USUARIO
	void control_Raton(int x, int y);
	void control_Gestos();

	// FUNCI�N RELACIONADA CON EL MOVIMIENTO DE LAS PIEZAS EN EL TABLERO
	void partida();

	// FUNCIONES RELACIONADAS CON EL MODO GR�FICO
	void dibuja();
	void dibuja_Menu();
};