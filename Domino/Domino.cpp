#include <iostream>
#include "Tablero.h"

int main(void) {
	Tablero tablero;
	int jugadores = 0, dificultad = 0;
	cout << "Simulador de Domino" << endl << endl;
	do {
		cout << "Selecciona el numero de jugadores (entre 2 y 4)" << endl;
		cout << "0: Salir del Programa" << endl;
		cin >> jugadores;
		if (jugadores == 0)
			return 0;
	} while (jugadores < 2 || jugadores>4);
	switch (jugadores) {
	case 0:
		break;
	default:
		do {
			cout << endl << "Selecciona la dificultad:" << endl;
			cout << "1: Facil" << endl;
			cout << "2: Intermedio" << endl;
			cout << "3: Dificil" << endl;
			cout << "0: Salir del Programa" << endl;
			cin >> dificultad;
			if(dificultad == 0)
				return 0;
		} while (dificultad < 1 || dificultad > 3);
		switch (dificultad) {
		case 0:
			break;
		default:
			tablero.partida(&jugadores, &dificultad);
			break;
		}
		break;
	}
	return 0;
}