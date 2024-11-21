#pragma once
#include "Ficha.h"


class Jugador {
private:
	int contador; // Sirve para contar cuantas fichas tiene el jugador
	Ficha fichas[7]; // Fichas de cada jugador
public:
	Jugador();
	int get_contador();
	Ficha get_ficha(int i);
	void vaciar_contenido();
	void cambiar_ficha(int pos = 0, int valor = 0);
	void anadir_ficha(int valor);
	int sin_fichas();
	int posibilidad_poner(Ficha tablero[], int cont_der, int cont_izq, int ficha = 0);

	// Funciones para el juego máquina
	void juego_IA(Ficha tablero[], int cont_der, int cont_izq, int* eleccion, int* eleccion_ficha, int* eleccion_lado, int dificultad);
	void modo_facil(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado);
	void modo_intermedio(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado);
	void modo_dificil(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado);

	// Funciones parte gráfica
	void dibuja(int jugador);
};