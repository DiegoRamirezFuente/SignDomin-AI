#include "Jugador.h"

Jugador::Jugador() {
	contador = -1;
	for (int i = 0; i < 7; i++)
		fichas[i].cambiar_ficha();
}

int Jugador::get_contador() {
	return contador;
}

Ficha Jugador::get_ficha(int i) {
	return fichas[i];
}

void Jugador::vaciar_contenido() {
	contador = -1;
	for (int i = 0; i < 28; i++)
		fichas[i].cambiar_ficha();
}

void Jugador::cambiar_ficha(int pos, int valor) {
	if (valor == 0) {
		for (int i = pos; i < contador + 1; i++)
			fichas[i].cambiar_ficha(fichas[i + 1].get_id());
		fichas[contador].cambiar_ficha();
		contador -= 1;
	}
	else {
		fichas[pos].cambiar_ficha(valor);
		contador += 1;
	}
}

void Jugador::anadir_ficha(int valor) {
	fichas[++contador].cambiar_ficha(valor);
}

// Esta función devuelve un 1 si el jugador se ha quedado sin fichas
int Jugador::sin_fichas() {
	for (int i = 0; i < contador + 1; i++) {
		if (fichas[i].get_id() != 0)
			return 0;
	}
	return 1;
}

// Esta función comprueba si el jugador puede poner ficha
// Devuelve 0 si el jugador no puede poner, 1 si puede poner por la derecha, 2 si puede poner por la izquiera y 3 si ambas
int Jugador::posibilidad_poner(Ficha tablero[], int cont_der, int cont_izq, int ficha) {
	int posibilidad = 0;
	if (ficha == 0) {
		for (int i = 0; i < contador + 1; i++) {
			if (tablero[cont_izq].get_lado() == 0) {
				if ((tablero[cont_izq].get_num1() == fichas[i].get_num1()) || (tablero[cont_izq].get_num1() == fichas[i].get_num2()))
					return 1;
			}
			if (tablero[cont_izq].get_lado() == 1) {
				if ((tablero[cont_izq].get_num2() == fichas[i].get_num1()) || (tablero[cont_izq].get_num2() == fichas[i].get_num2()))
					return 1;
			}
			if (tablero[cont_der].get_lado() == 0) {
				if ((tablero[cont_der].get_num2() == fichas[i].get_num1()) || (tablero[cont_der].get_num2() == fichas[i].get_num2()))
					return 1;
			}
			if (tablero[cont_der].get_lado() == 1) {
				if ((tablero[cont_der].get_num1() == fichas[i].get_num1()) || (tablero[cont_der].get_num1() == fichas[i].get_num2()))
					return 1;
			}
		}
	}
	else {
		if (tablero[cont_izq].get_lado() == 0) {
			if ((tablero[cont_izq].get_num1() == fichas[ficha - 1].get_num1()) || (tablero[cont_izq].get_num1() == fichas[ficha - 1].get_num2()))
				posibilidad += 2;
		}
		if (tablero[cont_izq].get_lado() == 1) {
			if ((tablero[cont_izq].get_num2() == fichas[ficha - 1].get_num1()) || (tablero[cont_izq].get_num2() == fichas[ficha - 1].get_num2()))
				posibilidad += 2;
		}
		if (tablero[cont_der].get_lado() == 0) {
			if ((tablero[cont_der].get_num2() == fichas[ficha - 1].get_num1()) || (tablero[cont_der].get_num2() == fichas[ficha - 1].get_num2()))
				posibilidad += 1;
		}
		if (tablero[cont_der].get_lado() == 1) {
			if ((tablero[cont_der].get_num1() == fichas[ficha - 1].get_num1()) || (tablero[cont_der].get_num1() == fichas[ficha - 1].get_num2()))
				posibilidad += 1;
		}
	}
	return posibilidad;
}

void Jugador::juego_IA(Ficha tablero[], int cont_der, int cont_izq, int* eleccion, int* eleccion_ficha, int* eleccion_lado, int dificultad) {
	int aux = 0;
	if (posibilidad_poner(tablero, cont_der, cont_izq) == 0) {
		*eleccion = 2; // Si no puede poner, pasa/roba
		return;
	}
	*eleccion = 1; // En caso de poder poner, elije poner
	if (dificultad == 1)
		modo_facil(tablero, cont_der, cont_izq, eleccion_ficha, eleccion_lado);
	else if (dificultad == 2)
		modo_intermedio(tablero, cont_der, cont_izq, eleccion_ficha, eleccion_lado);
	else if (dificultad == 3)
		modo_dificil(tablero, cont_der, cont_izq, eleccion_ficha, eleccion_lado);
}

void Jugador::modo_facil(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado) {
	int aux = 0;
	for (int i = 0; i < contador + 1; i++) {
		aux = posibilidad_poner(tablero, cont_der, cont_izq, i + 1);
		if (aux == 1 || aux == 3) { // Puede poner por la derecha
			*eleccion_ficha = i + 1;
			*eleccion_lado = 1;
			return;
		}
		if (aux == 2) { // Puede poner por la izquierda
			*eleccion_ficha = i + 1;
			*eleccion_lado = 2;
			return;
		}
	}
}

void Jugador::modo_intermedio(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado) {
	int repeticiones[7][2] = {0};
	int prioridad[7] = {0,1,2,3,4,5,6};

	// Cuenta cuantas veces aparece cada número en el tablero
	for (int i = cont_izq; i < cont_der + 1; i++) {
		switch (tablero[i].get_num1()){
			case 1:
				repeticiones[1][0] += 1;
				break;
			case 2:
				repeticiones[2][0] += 1;
				break;
			case 3:
				repeticiones[3][0] += 1;
				break;
			case 4:
				repeticiones[4][0] += 1;
				break;
			case 5:
				repeticiones[5][0] += 1;
				break;
			case 6:
				repeticiones[6][0] += 1;
				break;
			default:
				repeticiones[0][0] += 1;
				break;
		}
		switch (tablero[i].get_num2()) {
			case 1:
				repeticiones[1][0] += 1;
				break;
			case 2:
				repeticiones[2][0] += 1;
				break;
			case 3:
				repeticiones[3][0] += 1;
				break;
			case 4:
				repeticiones[4][0] += 1;
				break;
			case 5:
				repeticiones[5][0] += 1;
				break;
			case 6:
				repeticiones[6][0] += 1;
				break;
			default:
				repeticiones[0][0] += 1;
				break;
		}
	}

	// Cuenta cuantas veces aparece cada número en las fichas del propio jugador
	for (int i = 0; i < contador + 1; i++) {
		switch (fichas[i].get_num1()) {
			case 1:
				repeticiones[1][1] += 1;
				break;
			case 2:
				repeticiones[2][1] += 1;
				break;
			case 3:
				repeticiones[3][1] += 1;
				break;
			case 4:
				repeticiones[4][1] += 1;
				break;
			case 5:
				repeticiones[5][1] += 1;
				break;
			case 6:
				repeticiones[6][1] += 1;
				break;
			default:
				repeticiones[0][1] += 1;
				break;
		}
		switch (fichas[i].get_num2()) {
			case 1:
				repeticiones[1][1] += 1;
				break;
			case 2:
				repeticiones[2][1] += 1;
				break;
			case 3:
				repeticiones[3][1] += 1;
				break;
			case 4:
				repeticiones[4][1] += 1;
				break;
			case 5:
				repeticiones[5][1] += 1;
				break;
			case 6:
				repeticiones[6][1] += 1;
				break;
			default:
				repeticiones[0][1] += 1;
				break;
		}
	}

	// Ordenamos los números en orden de aparición
	for (int i = 0; i < 6; i++) {
		for (int j = 0; j < 6 - i; j++) {
			if (repeticiones[j][0] + repeticiones[j][1] < repeticiones[j + 1][0] + repeticiones[j + 1][1]) {
				int temp = prioridad[j];
				prioridad[j] = prioridad[j + 1];
				prioridad[j + 1] = temp;
			}
		}
	}

	// Intentamos poner pieza de forma que el número que quede en el extremo aparezca el mayor número de veces posible
	for (int j = 0; j < 7; j++) {
		for (int i = 0; i < contador + 1; i++) {
			if (tablero[cont_izq].get_lado() == 0) {
				if (tablero[cont_izq].get_num1() == fichas[i].get_num1() && (fichas[i].get_num2() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 2;
					return;
				}
				if (tablero[cont_izq].get_num1() == fichas[i].get_num2() && (fichas[i].get_num1() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 2;
					return;
				}
			}
			if (tablero[cont_izq].get_lado() == 1) {
				if (tablero[cont_izq].get_num2() == fichas[i].get_num1() && (fichas[i].get_num2() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 2;
					return;
				}
				if (tablero[cont_izq].get_num2() == fichas[i].get_num2() && (fichas[i].get_num1() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 2;
					return;
				}
			}
			if (tablero[cont_der].get_lado() == 0) {
				if (tablero[cont_der].get_num2() == fichas[i].get_num1() && (fichas[i].get_num2() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 1;
					return;
				}
				if (tablero[cont_der].get_num2() == fichas[i].get_num2() && (fichas[i].get_num1() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 1;
					return;
				}
			}
			if (tablero[cont_der].get_lado() == 1) {
				if (tablero[cont_der].get_num1() == fichas[i].get_num1() && (fichas[i].get_num2() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 1;
					return;
				}
				if (tablero[cont_der].get_num1() == fichas[i].get_num2() && (fichas[i].get_num1() == prioridad[j])) {
					*eleccion_ficha = i + 1;
					*eleccion_lado = 1;
					return;
				}
			}
		}
	}
}

void Jugador::modo_dificil(Ficha tablero[], int cont_der, int cont_izq, int* eleccion_ficha, int* eleccion_lado) {
	int aux = 0;
	for (int i = 0; i < 28; i++) {
		aux = posibilidad_poner(tablero, cont_der, cont_izq, i + 1);
		if (aux == 1 || aux == 3) { // Puede poner por la derecha
			*eleccion_ficha = i + 1;
			*eleccion_lado = 1;
			return;
		}
		if (aux == 2) { // Puede poner por la derecha
			*eleccion_ficha = i + 1;
			*eleccion_lado = 2;
			return;
		}
	}
}

void Jugador::dibuja(int jugador) {
	for (int i = 0; i < contador + 1; i++) {
		glDisable(GL_LIGHTING);
		glEnable(GL_TEXTURE_2D);
		if (jugador == 0) {
			fichas[i].dibuja(fichas[i].get_lado(), 'v');
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(9 + 2.7 * i, 6.5, 1);
			glTexCoord2d(1, 1);		glVertex3f(10.5 + 2.7 * i, 6.5, 1);
			glTexCoord2d(1, 0);		glVertex3f(10.5 + 2.7 * i, 9.5, 1);
			glTexCoord2d(0, 0);		glVertex3f(9 + 2.7 * i, 9.5, 1);
		}
		if (jugador == 1) {
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/fichaocultavertical.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(20 - 2.7 * i, 35, 1);
			glTexCoord2d(1, 1);		glVertex3f(21.5 - 2.7 * i, 35, 1);
			glTexCoord2d(1, 0);		glVertex3f(21.5 - 2.7 * i, 38, 1);
			glTexCoord2d(0, 0);		glVertex3f(20 - 2.7 * i, 38, 1);
		}
		if (jugador == 2) {
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/fichaocultahorizontal.png").id);
			glDisable(GL_LIGHTING); 
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(-3.5, 27.5 - 2.3 * i, 1);
			glTexCoord2d(1, 1);		glVertex3f(-0.5, 27.5 - 2.3 * i, 1);
			glTexCoord2d(1, 0);		glVertex3f(-0.5, 26 - 2.3 * i, 1);
			glTexCoord2d(0, 0);		glVertex3f(-3.5, 26 - 2.3 * i, 1);
		}
		if (jugador == 3) {
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/fichaocultahorizontal.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(31, 19 + 2.3 * i, 1);
			glTexCoord2d(1, 1);		glVertex3f(34, 19 + 2.3 * i, 1);
			glTexCoord2d(1, 0);		glVertex3f(34, 17.5 + 2.3 * i, 1);
			glTexCoord2d(0, 0);		glVertex3f(31, 17.5 + 2.3 * i, 1);
		}
		glEnd();
		glEnable(GL_LIGHTING);
		glDisable(GL_TEXTURE_2D);
	}
}