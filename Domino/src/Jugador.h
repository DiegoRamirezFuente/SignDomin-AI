#pragma once
#include "Ficha.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <sys/stat.h>
#include <thread>   // Para sleep_for
#include <chrono>   // Para chrono literals

class Jugador {
private:
	int contador; // Sirve para contar cuantas fichas tiene el jugador
	Ficha fichas[7]; // Fichas de cada jugador

	// Variables relacionadas con la lectura de las decisiones de la IA
	int numero;
	int pos = 0;
	int lugar = 0;
	const string filepath = "py/resultado.txt"; // Archivos donde se guardan las elecciones de la IA de cara a poner o no ficha
	void clearFile();
	bool isFileModified();
public:
	struct stat fileStat;
	Jugador();
	int get_contador() { return contador; }
	Ficha get_ficha(int i) { return fichas[i]; }
	void vaciar_contenido();
	void cambiar_ficha(int pos = 0, int valor = 0);
	int sin_fichas();
	int posibilidad_poner(Ficha tablero[], int cont_der, int cont_izq, int ficha = 0);

	// Funciones para el juego máquina
	void juego_IA(Ficha tablero[], int cont_der, int cont_izq, int* eleccion, int* eleccion_ficha, int* eleccion_lado, int dificultad);
	void conversion(int numero);
	void anti_errores(Ficha tablero[], int cont_der, int cont_izq, int* eleccion, int* eleccion_ficha, int* eleccion_lado);

	// Funciones relacionadas con la lectura del txt que indica la elección de la IA
	void lectura_solucion();

	// Funciones parte gráfica
	void dibuja(int jugador);
};