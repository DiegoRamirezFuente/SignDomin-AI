#pragma once
#include <iostream>
#include <windows.h>
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
	void default_id();
	int get_id();
	int get_num1();
	int get_num2();
	int get_lado();
	void cambiar_ficha(int id = 0, int lado = 0);
	void set_num1(int num1);
    void set_num2(int num2);
	// Funciones parte gráfica
	void dibuja(int lado, char pos);
};