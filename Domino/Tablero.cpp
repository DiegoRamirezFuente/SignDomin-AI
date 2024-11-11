#include <iostream>
#include <stdlib.h>
#include "Tablero.h"

Tablero::Tablero() {
	turno = 0;
	cont_der = 27;
	cont_izq = 27;
	for (int i = 0; i < 55; i++)
		tablero[i].cambiar_ficha();
	contador_pozo = -1;
	for (int i = 0; i < 28; i++)
		pozo[i].cambiar_ficha();
}

void Tablero::partida(int* jugadores, int* dificultad) {
	int eleccion = 0, ficha_robada = 0, posibilidad_total = 0;
	int eleccion_ficha = 0, posibilidad_ficha = 0;
	int eleccion_lado = 0;

	// El primer paso de la partida es repartir las fichas
	reparto_fichas(jugadores);
	primer_turno(jugadores);

	// Este bucle contiene todo el juego
	do {
		cambio_turno(jugadores);
		mostrar_tablero(jugadores);
		if (turno == 0) { // Nosotros controlamos el jugador local
			// Primero analizamos si el jugador puede poner o no
			do {
				ficha_robada = 0;
				posibilidad_total = this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq);
				cout << endl << "Es el turno del jugador " << turno + 1 << ". Elija que quiere hacer:" << endl;
				cout << "1: Poner" << endl;
				cout << "2: Robar el pozo/pasar" << endl;
				cin >> eleccion;
				if (eleccion == 1 && posibilidad_total == 0)
					cout << "No puedes poner ficha, tienes que robar/pasar" << endl;
				if (eleccion == 2)
					ficha_robada = robar_ficha(jugadores);
			} while ((eleccion == 1 && posibilidad_total == 0) || (ficha_robada == 1));

			// Dependiendo de si elegimos poner o pasar
			switch (eleccion) {
			case 1: // Si elejimos poner
				do {
					cout << endl << "Has elegido poner, elija la ficha que desea colocar:" << endl;
					cin >> eleccion_ficha;
					posibilidad_ficha = this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha);
					if (posibilidad_ficha == 0)
						cout << "Esa ficha no la puedes poner, elije otra" << endl;
				} while (posibilidad_ficha == 0);

				// Una vez elegida que ficha, elegimos el lado por el cual la queremos poner
				do {
					cout << endl << "Elija el lado:" << endl;
					cout << "1: Poner por la derecha" << endl;
					cout << "2: Poner por la izquierda" << endl;
					cin >> eleccion_lado;
					if (eleccion_lado == 1 && posibilidad_ficha == 2)
						cout << "Solo puedes poner esta ficha por la izquierda" << endl;
					if (eleccion_lado == 2 && posibilidad_ficha == 1)
						cout << "Solo puedes poner esta ficha por la derecha" << endl;
				} while ((eleccion_lado == 1 && posibilidad_ficha == 2) || (eleccion_lado == 2 && posibilidad_ficha == 1));
				colocar_ficha(&eleccion_ficha, &eleccion_lado);
			}
		}
		else { // El jugador máquina juega solo
			do {
				ficha_robada = 0;
				this->jugadores[turno].juego_IA(tablero, cont_der, cont_izq, &eleccion, &eleccion_ficha, &eleccion_lado, dificultad);
				if (eleccion == 2 && contador_pozo > -1)
					ficha_robada = robar_ficha(jugadores);
			} while (ficha_robada == 1);
			if (eleccion == 1)
				colocar_ficha(&eleccion_ficha, &eleccion_lado);
		}
	} while (final_partida(jugadores) == 0);
	mostrar_tablero(jugadores);
	cout << endl << "EL JUGADOR " << turno + 1 << " HA GANADO LA PARTIDA" << endl;
}

// Esta función sirve para repartir las fichas al comienza de la partida
void Tablero::reparto_fichas(int* jugadores) {
	int aleatorio, igual, valores[28] = { 0 };
	srand(time(0)); // Establece la semilla para la generación de números aleatorios
	for (int i = 0; i < 28; i++) {
		do {
			igual = 0;
			aleatorio = 1 + (rand() % 28);; // Genero valores aleaorios entre 1 y 28
			for (int j = 0; j < i; j++) {
				if (aleatorio == valores[j])
					igual = 1;
			}
		} while (igual == 1); // si un numero se repite, se genero otro
		valores[i] = aleatorio;
	}
	// Este bucle sirve para repartir las fichas entre el numero de jugadores
	for (int i = 0; i < 7; i++) {
		this->jugadores[0].cambiar_ficha(i, valores[i]);
		this->jugadores[1].cambiar_ficha(i, valores[i + 7]);
		this->jugadores[2].cambiar_ficha(i, valores[i + 14]);
		this->jugadores[3].cambiar_ficha(i, valores[i + 21]);
		if (*jugadores == 2) {
			pozo[i].cambiar_ficha(valores[i + 14]);
			pozo[i + 7].cambiar_ficha(valores[i + 21]);
			this->jugadores[2].cambiar_ficha(i);
			this->jugadores[3].cambiar_ficha(i);
			contador_pozo = 13;
		}
		if (*jugadores == 3) {
			pozo[i].cambiar_ficha(valores[i + 21]);
			this->jugadores[3].cambiar_ficha(i);
			contador_pozo = 6;
		}
	}
}

// Esta función determina quien tiene la ficha más alta y empieza a jugar
void Tablero::primer_turno(int* jugadores) {
	int max = 0;
	for (int i = 0; i < 7; i++) {
		if (this->jugadores[0].get_ficha(i).get_id() > max) {
			max = this->jugadores[0].get_ficha(i).get_id();
			turno = 0; // El turno del jugador 1 lo simbolizo con el numero 0
		}
		if (this->jugadores[1].get_ficha(i).get_id() > max) {
			max = this->jugadores[1].get_ficha(i).get_id();
			turno = 1; // El turno del jugador 2 lo simbolizo con el numero 1
		}
		if (*jugadores > 2) {
			if (this->jugadores[2].get_ficha(i).get_id() > max) {
				max = this->jugadores[2].get_ficha(i).get_id();
				turno = 2; // El turno del jugador 3 lo simbolizo con el numero 2
			}
		}
		if (*jugadores > 3) {
			if (this->jugadores[3].get_ficha(i).get_id() > max) {
				max = this->jugadores[3].get_ficha(i).get_id();
				turno = 3; // El turno del jugador 4 lo simbolizo con el numero 3
			}
		}
	}
	mostrar_tablero(jugadores);

	// Además, el primer turno es siempre el mismo ya que esta obligado a poner la ficha más alta
	for (int i = 0; i < 7; i++) {
		if (this->jugadores[0].get_ficha(i).get_id() == max) {
			tablero[27].cambiar_ficha(max); // Coloca la ficha en el tablero
			this->jugadores[0].cambiar_ficha(i); // le quita la ficha al jugador
			return;
		}
		if (this->jugadores[1].get_ficha(i).get_id() == max) {
			tablero[27].cambiar_ficha(max);
			this->jugadores[1].cambiar_ficha(i);
			return;
		}
		if (*jugadores > 2) {
			if (this->jugadores[2].get_ficha(i).get_id() == max) {
				tablero[27].cambiar_ficha(max);
				this->jugadores[2].cambiar_ficha(i);
				return;
			}
		}
		if (*jugadores > 3) {
			if (this->jugadores[3].get_ficha(i).get_id() == max) {
				tablero[27].cambiar_ficha(max);
				this->jugadores[3].cambiar_ficha(i);
				return;
			}
		}
	}
}

void Tablero::cambio_turno(int* jugadores) {
	turno = (turno + 1) % *jugadores;
}

void Tablero::colocar_ficha(int* eleccion_ficha, int* eleccion_lado) {
	if (*eleccion_lado == 1) { // Ponemos por la derecha
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
	}
	if (*eleccion_lado == 2) { // Ponemos por la izquierda
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(*eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(*eleccion_ficha - 1);
			return;
		}
	}
}

int Tablero::robar_ficha(int* jugadores) {
	if (contador_pozo == -1)
		return 0;
	this->jugadores[turno].anadir_ficha(pozo[contador_pozo].get_id());
	pozo[contador_pozo--].cambiar_ficha();
	mostrar_tablero(jugadores);
	return 1;
}

int Tablero::final_partida(int* jugadores) {
	if (this->jugadores[turno].sin_fichas() == 1) // 1 si el jugador se ha quedado sin fichas
		return 1;
	for (int i = 0; i < *jugadores; i++) {
		if (i != turno) {
			if (this->jugadores[i].posibilidad_poner(tablero, cont_der, cont_izq) == 1)
				return 0;
		}
	}
	return 1;
}

void Tablero::mostrar_tablero(int* jugadores) {
	cout << endl << endl << "TURNO DEL JUGADOR " << turno + 1 << endl;
	cout << endl << "Tablero:";
	for (int i = cont_izq; i < cont_der + 1; i++)
		tablero[i].mostrar_ficha();
	cout << endl << "Jugador 1:";
	this->jugadores[0].mostrar_fichas();
	cout << endl << "Jugador 2:";
	this->jugadores[1].mostrar_fichas();
	if (*jugadores > 2) {
		cout << endl << "Jugador 3:";
		this->jugadores[2].mostrar_fichas();
	}
	if (*jugadores > 3) {
		cout << endl << "Jugador 4:";
		this->jugadores[3].mostrar_fichas();
	}
	if (*jugadores < 4) {
		cout << endl << "Pozo:";
		for (int i = 0; i < contador_pozo + 1; i++)
			pozo[i].mostrar_ficha();
	}
}