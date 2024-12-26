#pragma once
#include "Ficha.h"
#include "Jugador.h"
#include "GestureReader.h"

class Tablero {
private:
	int primer_movimiento; // Para saber si el primer turno se ha ejecutado ya
	int movimiento_controlado;
	int turno; // Variable que sirve para saber a quien le toca jugar
	int inicio; // Para saber cuando empieza una nueva partida
	int fin; // Para saber cuando ha terminado la partida
	
	// CONJUNTO DE VARIABLES PARA REGULAR EL TABLERO
	int cont_der;
	int cont_izq;
	Ficha tablero[55]; // Vector que contiene las fichas que ya han sido introducidas

	// HAY 4 JUGADORES
	Jugador jugadores[4];

	//PARA ESCRIBIR EN UN ARCHIVO
	ofstream archivo;
	int escribir[20];

	// CONJUNTO DE VARIABLES PARA CONTROLAR LAS ELECCIONES DEL JUGADOR
	int eleccion;
	int eleccion_ficha;
	int eleccion_lado;
public:
	Tablero();
	void partida(int dificultad);
	void cambio_turno();
	void colocar_ficha();
	void final_partida();
	int get_final() { return fin; }

	// FUNCIONES RELACIONADAS CON EL CONTROL DE LAS ELECCIONES DEL USUARIO
	void control_Raton(int x, int y);
	void control_Gestos(GestureReader* gesto);

	// Estas funciones sirven para determinar el primer turno
	void partida_nueva();
	void reparto_fichas();
	void primer_turno();

	int eleccion_final(int posicion, int lugar);
	void dibuja(int* modo);
};