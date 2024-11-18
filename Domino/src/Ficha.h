#pragma once
#include <iostream>
#include <windows.h>
#include <thread>
#include <string>
#include <fstream>
#include <stdexcept>
#include <chrono>
#include <sys/stat.h> 
#include "freeglut.h"
#include "ETSIDI.h"

using namespace std;
using namespace ETSIDI;

class Ficha {
private:
	int identificador = 0; // Sirve para saber que pieza es
	int numero1 = 0; // Primer numero de la ficha
	int numero2 = 0; // Segundo número de la ficha
	int lado = 0; // Si vale 0 es [numero1,numero2]; pero si es 1 es [numero2,numero1]
public:
	int get_id() { return identificador; }
	int get_num1() { return numero1; }
	int get_num2() { return numero2; }
	int get_lado() { return lado; }
	void cambiar_ficha(int id = 0, int lado = 0);

	// Funciones parte gráfica
	void dibuja(int lado, char pos);
};