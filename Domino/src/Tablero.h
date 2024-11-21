#pragma once
#include "Ficha.h"
#include "Jugador.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>

class Tablero {
private:
	int primer_movimiento; // Para saber si el primer turno se ha ejecutado ya
	int turno; // Variable que sirve para saber a quien le toca jugar
	int turno_desfasado; //se utiliza para poner bien en el vector de ficha jugada
	int inicio; // Para saber cuando empieza una nueva partida
	int fin;

	// CONJUNTO DE VARIABLES PARA REGULAR EL TABLERO
	int cont_der;
	int cont_izq;
	Ficha tablero[55]; // Vector que contiene las fichas que ya han sido introducidas

	// HAY 4 JUGADORES
	Jugador jugadores[4];

	// CONJUNTO DE VARIABLES PARA CONTROLAR LAS ELECCIONES DEL JUGADOR
	int eleccion;
	int eleccion_ficha;
	int eleccion_lado;

	//PARA ESCRIBIR EN UN .CSV
	ofstream archivo;

	//vectores bidimensionales para almacenar toda la informacion necesaria para pasarla al excel

	//vector<vector<int>> Turno_jugador; //vector bidimensional para guaradar el turno de cada jugador.
	//vector<vector<vector<Ficha>>> Mano_jugador; //vector tridimensional para gardar las fichas que tiene cada jugador cada turno turno.
	//vector<vector<Ficha>> Tablero_turno; //vector bidimensional para guardar los extremos del tablero se usaran numeros de fichas(num1 sera la izq y num2 sera la derecha).
	//vector<vector<Ficha>> Ficha_jugada; //ficha jugada por cada jugador en cada turno.

	int   Turno_jugador[4][100];   //hecho
	Ficha Mano_jugador[4][100][7];// hecho
	Ficha Tablero_turno[4][100]; //  hecho
	Ficha Ficha_jugada[4][100]; //   hecho
	int seleccion_absoluta[4][100];

	int ficha_puesta = 0;
	int veces_jugadas = 0;
public:
	Tablero();
	void partida(int dificultad);
	void cambio_turno();
	Ficha colocar_ficha();
	void final_partida();
	int get_final() { return fin; }
	void set_final(int x) { fin = x; }

	// Control por ratón
	void control_Raton(int x, int y);

	// Estas funciones sirven para determinar el primer turno
	void partida_nueva();
	void reparto_fichas();
	void primer_turno();

	//Funciones para pasar la informacion a la red neuronal
	int eleccion_final(int posicion, int lugar);

	// Funciones parte gráfica
	void dibuja();
};