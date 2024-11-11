#include <iostream>
#include "Ficha.h"

int Ficha::get_id() {
	return identificador;
}

int Ficha::get_num1() {
	return numero1;
}

int Ficha::get_num2() {
	return numero2;
}

int Ficha::get_lado() {
	return lado;
}

void Ficha::cambiar_ficha(int id, int lado) {
	switch (id) {
		case 1:
			identificador = 1;
			numero1 = 0;
			numero2 = 1;
			this->lado = lado;
			break;
		case 2:
			identificador = 2;
			numero1 = 0;
			numero2 = 2;
			this->lado = lado;
			break;
		case 3:
			identificador = 3;
			numero1 = 0;
			numero2 = 3;
			this->lado = lado;
			break;
		case 4:
			identificador = 4;
			numero1 = 0;
			numero2 = 4;
			this->lado = lado;
			break;
		case 5:
			identificador = 5;
			numero1 = 0;
			numero2 = 5;
			this->lado = lado;
			break;
		case 6:
			identificador = 6;
			numero1 = 0;
			numero2 = 6;
			this->lado = lado;
			break;
		case 7:
			identificador = 7;
			numero1 = 1;
			numero2 = 2;
			this->lado = lado;
			break;
		case 8:
			identificador = 8;
			numero1 = 1;
			numero2 = 3;
			this->lado = lado;
			break;
		case 9:
			identificador = 9;
			numero1 = 1;
			numero2 = 4;
			this->lado = lado;
			break;
		case 10:
			identificador = 10;
			numero1 = 1;
			numero2 = 5;
			this->lado = lado;
			break;
		case 11:
			identificador = 11;
			numero1 = 1;
			numero2 = 6;
			this->lado = lado;
			break;
		case 12:
			identificador = 12;
			numero1 = 2;
			numero2 = 3;
			this->lado = lado;
			break;
		case 13:
			identificador = 13;
			numero1 = 2;
			numero2 = 4;
			this->lado = lado;
			break;
		case 14:
			identificador = 14;
			numero1 = 2;
			numero2 = 5;
			this->lado = lado;
			break;
		case 15:
			identificador = 15;
			numero1 = 2;
			numero2 = 6;
			this->lado = lado;
			break;
		case 16:
			identificador = 16;
			numero1 = 3;
			numero2 = 4;
			this->lado = lado;
			break;
		case 17:
			identificador = 17;
			numero1 = 3;
			numero2 = 5;
			this->lado = lado;
			break;
		case 18:
			identificador = 18;
			numero1 = 3;
			numero2 = 6;
			this->lado = lado;
			break;
		case 19:
			identificador = 19;
			numero1 = 4;
			numero2 = 5;
			this->lado = lado;
			break;
		case 20:
			identificador = 20;
			numero1 = 4;
			numero2 = 6;
			this->lado = lado;
			break;
		case 21:
			identificador = 21;
			numero1 = 5;
			numero2 = 6;
			this->lado = lado;
			break;
		case 22:
			identificador = 22;
			numero1 = 0;
			numero2 = 0;
			this->lado = lado;
			break;
		case 23:
			identificador = 23;
			numero1 = 1;
			numero2 = 1;
			this->lado = lado;
			break;
		case 24:
			identificador = 24;
			numero1 = 2;
			numero2 = 2;
			this->lado = lado;
			break;
		case 25:
			identificador = 25;
			numero1 = 3;
			numero2 = 3;
			this->lado = lado;
			break;
		case 26:
			identificador = 26;
			numero1 = 4;
			numero2 = 4;
			this->lado = lado;
			break;
		case 27:
			identificador = 27;
			numero1 = 5;
			numero2 = 5;
			this->lado = lado;
			break;
		case 28:
			identificador = 28;
			numero1 = 6;
			numero2 = 6;
			this->lado = lado;
			break;
		default:
			identificador = 0;
			numero1 = 0;
			numero2 = 0;
			this->lado = lado;
			break;
	}
}

void Ficha::mostrar_ficha() {
	if (identificador != 0) {
		if (lado == 0)
			cout << " [" << numero1 << "|" << numero2 << "] ";
		if (lado == 1)
			cout << " [" << numero2 << "|" << numero1 << "] ";
	}
}