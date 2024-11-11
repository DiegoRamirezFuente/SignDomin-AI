#pragma once

using namespace std;

class Ficha {
private:
	int identificador = 0; // Sirve para saber que pieza es
	int numero1 = 0; // Primer numero de la ficha
	int numero2 = 0; // Segundo número de la ficha
	int lado = 0; // Si vale 0 es [numero1,numero2]; pero si es 1 es [numero2,numero1]
public:
	int get_id();
	int get_num1();
	int get_num2();
	int get_lado();
	void cambiar_ficha(int id = 0, int lado = 0);

	// Funciones parte gráfica
	void mostrar_ficha();
};