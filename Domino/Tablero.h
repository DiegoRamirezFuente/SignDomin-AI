#pragma once
#include "Ficha.h"
#include "Jugador.h"

class Tablero {
private:
	int turno; // Variable que sirve para saber a quien le toca jugar

	int cont_der;
	int cont_izq;
	Ficha tablero[55]; // Vector que contiene las fichas que ya han sido introducidas

	Jugador jugadores[4]; // Puede haber hasta un máximo de 4 jugadores

	int contador_pozo; // Cuenta las fichas que hay en el pozo
	Ficha pozo[28]; // Vector que contiene las fichas del pozo
public:
	Tablero();
	void partida(int* jugadores, int* dificultad);
	void reparto_fichas(int* jugadores);
	void primer_turno(int* jugadores);
	void cambio_turno(int* jugadores);
	void colocar_ficha(int* eleccion_ficha, int* eleccion_lado);
	int robar_ficha(int* jugadores);
	int final_partida(int* jugadores);

	// Funciones parte gráfica
	void mostrar_tablero(int* jugadores);
};