#include "Tablero.h"
#include "GestureReader.h"
GestureReader g_tab;
Tablero::Tablero() {
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
	turno = - 1;
	fin = 0;
	cont_der = 27;
	cont_izq = 27;
	for (int i = 0; i < 55; i++)
		tablero[i].cambiar_ficha();
}

void Tablero::partida(int dificultad) {
	int posibilidad_total = 0;
	int posibilidad_ficha = 0;

	if (inicio == 0) {
		inicio = 1;
		eleccion = 0;
		eleccion_ficha = 0;
		eleccion_lado = 0;
		turno = -1;
		fin = 0;
		cont_der = 27;
		cont_izq = 27;
		for (int i = 0; i < 55; i++)
			tablero[i].cambiar_ficha();
		for (int i = 0; i < 4; i++)
			this->jugadores[i].vaciar_contenido();

		// Generamos el primer turno
		reparto_fichas();
		dibuja();
		primer_turno();
		dibuja();
		cambio_turno();
	}

	final_partida();
	if (fin == 0) {
		if (turno == 0) { // Nosotros controlamos el jugador local
			if (eleccion != 0) {
				posibilidad_total = this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq);
				if (eleccion == 1 && posibilidad_total == 0)
					eleccion = 0;
				else if (eleccion == 2)
					cambio_turno();
				if (eleccion == 1 && posibilidad_total == 1) {
					if (eleccion_ficha != 0) {
						posibilidad_ficha = this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha);
						if (posibilidad_ficha == 0)
							eleccion_ficha = 0;
						else {
							if (eleccion_lado != 0) {
								if (posibilidad_ficha == 1 && eleccion_lado == 2)
									eleccion_lado = 0;
								else if (posibilidad_ficha == 2 && eleccion_lado == 1)
									eleccion_lado = 0;
								else 
									colocar_ficha();
								
							}
						}
					}
				}
			}
		}
		else { // El jugador máquina juega solo
			this->jugadores[turno].juego_IA(tablero, cont_der, cont_izq, &eleccion, &eleccion_ficha, &eleccion_lado, dificultad);
			if (eleccion == 1)
				colocar_ficha();
			if (eleccion == 2)
				cambio_turno();
			Sleep(2000);
		}
	}
	else {
		cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
	}
}

void Tablero::cambio_turno() {
	turno = (turno + 1) % 4;
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
}

void Tablero::colocar_ficha() {
	if (eleccion_lado == 1) { // Ponemos por la derecha
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
	}
	if (eleccion_lado == 2) { // Ponemos por la izquierda
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			cambio_turno();
			return;
		}
	}
}

void Tablero::final_partida() {
	if (this->jugadores[turno].sin_fichas() == 1) { // 1 si el jugador se ha quedado sin fichas
		fin = 1;
		return;
	}
	for (int i = 0; i < 4; i++) {
		if (i != turno) {
			if (this->jugadores[i].posibilidad_poner(tablero, cont_der, cont_izq) == 1)
				return;
		}
	}
	fin = 1;
	return;
}

void Tablero::control_Raton(int x, int y) {
	if (turno == 0) {
		if (eleccion == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267) {
				x = 0;
				y = 0;
				eleccion = 1;
				
			}
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475) {
				x = 0;
				y = 0;
				eleccion = 2;
				x = 0;
				y = 0;
			}
		}
		else if (eleccion != 0 && eleccion_ficha == 0) {
			if (x >= 282 && x <= 311 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 1;
				
			}
			else if (x >= 337 && x <= 364 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 2;
			
			}
			else if (x >= 389 && x <= 418 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 3;
				;
			}
			else if (x >= 444 && x <= 471 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 4;
				
			}
			else if (x >= 497 && x <= 525 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 5;
				
			}
			else if (x >= 551 && x <= 578 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 6;
			
			}
			else if (x >= 604 && x <= 633 && y >= 545 && y <= 600) {
				x = 0;
				y = 0;
				eleccion_ficha = 7;
			}
			else {
				x = 0;
				y = 0;
				eleccion = 0;
			
			}
				
		}
		else if (eleccion != 0 && eleccion_ficha != 0 && eleccion_lado == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267) {
				x = 0;
				y = 0;
				eleccion_lado = 2;
				
			}
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475) {
				x = 0;
				y = 0;
				eleccion_lado = 1;
				
			}
			else {
				x = 0;
				y = 0;
				eleccion_ficha = 0;
				
			}
				
		}
	}
}
void Tablero::control_gesto() {
	if (turno == 0) {
		if (eleccion == 0) {
			if (g_tab.get_gesture() == 6) 
				eleccion = 1;
			if (g_tab.get_gesture() == 7)
				eleccion = 2;
			
		}
		else if (eleccion != 0 && eleccion_ficha == 0) {
			if (g_tab.get_gesture() == 1)
				eleccion_ficha == 1;
			if (g_tab.get_gesture() == 2)
				eleccion_ficha == 2;
			if (g_tab.get_gesture() == 3)
				eleccion_ficha == 3;
			if (g_tab.get_gesture() == 4)
				eleccion_ficha == 4;
			if (g_tab.get_gesture() == 5)
				eleccion_ficha == 5;
			if (g_tab.get_gesture() == 8)
				eleccion_ficha == 6;
			if (g_tab.get_gesture() == 9)
				eleccion_ficha == 7;
		}
	}
	
}

void Tablero::partida_nueva() {
	inicio = 0;
}

// Esta función sirve para repartir las fichas al comienza de la partida
void Tablero::reparto_fichas() {
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
	}
}

// Esta función determina quien tiene la ficha más alta y empieza a jugar
void Tablero::primer_turno() {
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
		if (this->jugadores[2].get_ficha(i).get_id() > max) {
			max = this->jugadores[2].get_ficha(i).get_id();
			turno = 2; // El turno del jugador 3 lo simbolizo con el numero 2
		}
		if (this->jugadores[3].get_ficha(i).get_id() > max) {
			max = this->jugadores[3].get_ficha(i).get_id();
			turno = 3; // El turno del jugador 4 lo simbolizo con el numero 3
		}
	}

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
		if (this->jugadores[2].get_ficha(i).get_id() == max) {
			tablero[27].cambiar_ficha(max);
			this->jugadores[2].cambiar_ficha(i);
			return;
		}
		if (this->jugadores[3].get_ficha(i).get_id() == max) {
			tablero[27].cambiar_ficha(max);
			this->jugadores[3].cambiar_ficha(i);
			return;
		}
	}
}

void Tablero::dibuja() {
	gluLookAt(20, 20, 53,  // posicion del ojo
		20, 20, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y)

	// Pintamos el tablero
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/tablero.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-6, 5, 0);
	glTexCoord2d(1, 1);		glVertex3f(36, 5, 0);
	glTexCoord2d(1, 0);		glVertex3f(36, 40, 0);
	glTexCoord2d(0, 0);		glVertex3f(-6, 40, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Pintamos el turno
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	if (turno == 0) 
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno1.png").id);
	else if (turno == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno2.png").id);
	else if (turno == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno3.png").id);
	else if (turno == 3)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno4.png").id);
	else
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/negro.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-6, 0, 0);
	glTexCoord2d(1, 1);		glVertex3f(36, 0, 0);
	glTexCoord2d(1, 0);		glVertex3f(36, 5, 0);
	glTexCoord2d(0, 0);		glVertex3f(-6, 5, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Pintamos las elecciones
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	if (turno == 0) {
		if (eleccion == 0)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Poner-Pasar.png").id);
		else if (eleccion_ficha == 0)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/negro.png").id);
		else
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Izq-Dcha.png").id);
	}
	else
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/negro.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(36, 0, 0);
	glTexCoord2d(1, 1);		glVertex3f(46, 0, 0);
	glTexCoord2d(1, 0);		glVertex3f(46, 40, 0);
	glTexCoord2d(0, 0);		glVertex3f(36, 40, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);

	// Pintamos las fichas del tablero
	for (int i = cont_izq; i < cont_der + 1; i++) {
		if (tablero[i].get_id() != 0) {
			glDisable(GL_LIGHTING);
			glEnable(GL_TEXTURE_2D);
			if (i >= 0 && i <= 1) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(12.8 - 3 * (i - 0), 29.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(12.8 - 3 * (i + 1), 29.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(12.8 - 3 * (i + 1), 28.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(12.8 - 3 * (i - 0), 28.05, 1);
			}
			else if (i == 2) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(5.3, 26.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(6.8, 26.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(6.8, 29.55, 1);
				glTexCoord2d(0, 0);		glVertex3f(5.3, 29.55, 1);
			}
			else if (i >= 3 && i <= 9) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(5.3 + 3 * (i - 3), 26.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(5.3 + 3 * (i - 2), 26.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(5.3 + 3 * (i - 2), 25.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(5.3 + 3 * (i - 3), 25.05, 1);
			}
			else if (i >= 10 && i <= 11) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(26.3, 25.05 + 3 * (i - 9), 1);
				glTexCoord2d(1, 1);		glVertex3f(27.8, 25.05 + 3 * (i - 9), 1);
				glTexCoord2d(1, 0);		glVertex3f(27.8, 25.05 + 3 * (i - 10), 1);
				glTexCoord2d(0, 0);		glVertex3f(26.3, 25.05 + 3 * (i - 10), 1);
			}
			else if (i >= 12 && i <= 19) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(27.8 - 3 * (i - 12), 32.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(27.8 - 3 * (i - 11), 32.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(27.8 - 3 * (i - 11), 31.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(27.8 - 3 * (i - 12), 31.05, 1);
			}
			else if (i >= 20 && i <= 22) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(2.3, 32.55 - 3 * (i - 19), 1);
				glTexCoord2d(1, 1);		glVertex3f(3.8, 32.55 - 3 * (i - 19), 1);
				glTexCoord2d(1, 0);		glVertex3f(3.8, 32.55 - 3 * (i - 20), 1);
				glTexCoord2d(0, 0);		glVertex3f(2.3, 32.55 - 3 * (i - 20), 1);
			}
			else if (i >= 23 && i <= 26) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(5.3 + 3 * (i - 24), 22.05, 1);
				glTexCoord2d(1, 1);		glVertex3f(5.3 + 3 * (i - 23), 22.05, 1);
				glTexCoord2d(1, 0);		glVertex3f(5.3 + 3 * (i - 23), 23.55, 1);
				glTexCoord2d(0, 0);		glVertex3f(5.3 + 3 * (i - 24), 23.55, 1);
			}
			else if (i == 27) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(14.3, 21.3, 1);
				glTexCoord2d(1, 1);		glVertex3f(15.8, 21.3, 1);
				glTexCoord2d(1, 0);		glVertex3f(15.8, 24.3, 1);
				glTexCoord2d(0, 0);		glVertex3f(14.3, 24.3, 1);
			}
			else if (i >= 28 && i <= 31) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(15.8 + 3 * (i - 28), 22.05, 1);
				glTexCoord2d(1, 1);		glVertex3f(15.8 + 3 * (i - 27), 22.05, 1);
				glTexCoord2d(1, 0);		glVertex3f(15.8 + 3 * (i - 27), 23.55, 1);
				glTexCoord2d(0, 0);		glVertex3f(15.8 + 3 * (i - 28), 23.55, 1);
			}
			else if (i >= 32 && i <= 34) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(26.3, 22.05 - 3 * (i - 31), 1);
				glTexCoord2d(1, 1);		glVertex3f(27.8, 22.05 - 3 * (i - 31), 1);
				glTexCoord2d(1, 0);		glVertex3f(27.8, 22.05 - 3 * (i - 32), 1);
				glTexCoord2d(0, 0);		glVertex3f(26.3, 22.05 - 3 * (i - 32), 1);
			}
			else if (i >= 35 && i <= 42) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(23.3 - 3 * (i - 36), 13.05, 1);
				glTexCoord2d(1, 1);		glVertex3f(23.3 - 3 * (i - 35), 13.05, 1);
				glTexCoord2d(1, 0);		glVertex3f(23.3 - 3 * (i - 35), 14.55, 1);
				glTexCoord2d(0, 0);		glVertex3f(23.3 - 3 * (i - 36), 14.55, 1);
			}
			else if (i >= 43 && i <= 44) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(2.3, 17.55 + 3 * (i - 43), 1);
				glTexCoord2d(1, 1);		glVertex3f(3.8, 17.55 + 3 * (i - 43), 1);
				glTexCoord2d(1, 0);		glVertex3f(3.8, 17.55 + 3 * (i - 44), 1);
				glTexCoord2d(0, 0);		glVertex3f(2.3, 17.55 + 3 * (i - 44), 1);
			}
			else if (i >= 45 && i <= 51) {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(3.8 + 3 * (i - 45), 20.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(3.8 + 3 * (i - 44), 20.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(3.8 + 3 * (i - 44), 19.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(3.8 + 3 * (i - 45), 19.05, 1);
			}
			else if (i == 52) {
				tablero[i].dibuja(tablero[i].get_lado(), 'v');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(23.3, 16.05, 1);
				glTexCoord2d(1, 1);		glVertex3f(24.8, 16.05, 1);
				glTexCoord2d(1, 0);		glVertex3f(24.8, 19.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(23.3, 19.05, 1);
			}
			else {
				tablero[i].dibuja(tablero[i].get_lado(), 'h');
				glDisable(GL_LIGHTING);
				glBegin(GL_POLYGON);
				glColor3f(1, 1, 1);
				glTexCoord2d(0, 1);		glVertex3f(20.3 - 3 * (i - 54), 17.55, 1);
				glTexCoord2d(1, 1);		glVertex3f(20.3 - 3 * (i - 53), 17.55, 1);
				glTexCoord2d(1, 0);		glVertex3f(20.3 - 3 * (i - 53), 16.05, 1);
				glTexCoord2d(0, 0);		glVertex3f(20.3 - 3 * (i - 54), 16.05, 1);
			}
			glEnd();
			glEnable(GL_LIGHTING);
			glDisable(GL_TEXTURE_2D);
		}
	}

	// Pintamos las fichas de cada jugador
	for (int i = 0; i < 4; i++)
		jugadores[i].dibuja(i);
}