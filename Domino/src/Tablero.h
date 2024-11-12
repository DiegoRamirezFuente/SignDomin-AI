#pragma once
#include "Ficha.h"
#include "Jugador.h"

class Tablero {
private:
	int turno; // Variable que sirve para saber a quien le toca jugar
	int inicio; // Para saber cuando empieza una nueva partida
	int fin;

	// CONJUNTO DE VARIABLES PARA REGULAR EL TABLERO
	int cont_der;
	int cont_izq;
	Ficha tablero[55]; // Vector que contiene las fichas que ya han sido introducidas

	// HAY HASTA UN MÁXIMO DE 4 JUGADORES
	Jugador jugadores[4];

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

	// Control por ratón
	void control_Raton(int x, int y);

	// Estas funciones sirven para determinar el primer turno
	void partida_nueva();
	void reparto_fichas();
	void primer_turno();

	// Funciones parte gráfica
	void dibuja();
};