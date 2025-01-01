#include "Tablero.h"

int sonido_final;

Tablero::Tablero() {
	primer_movimiento = 0;
	movimiento_controlado = 0;
	turno = -1;
	inicio = 0;
	fin = 0;
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
	cont_der = 27;
	cont_izq = 27;
}

void Tablero::partida(int dificultad) {
	if (inicio == 0) {
		inicio = 1;
		reparto_fichas();
		Sleep(2000);
	}
	else if (inicio == 1) {
		inicio = 2;
		primer_turno();
		primer_movimiento = 1;
		cambio_turno(); // Cambiamos el turno
		Sleep(2000);
	}
	else {
		if (fin == 0) {
			if (turno == 0 && movimiento_controlado == 0) { // Nosotros controlamos el jugador local
				if (tablero[cont_izq].get_lado() == 0) {
					escribir[1] = tablero[cont_izq].get_num1();// numero en la izq 
				}
				else if (tablero[cont_izq].get_lado() == 1) {
					escribir[1] = tablero[cont_izq].get_num2(); // numero en la izq 
				}
				if (tablero[cont_der].get_lado() == 0) {
					escribir[2] = tablero[cont_der].get_num2();// numero en la drcha
				}
				else if (tablero[cont_der].get_lado() == 1) {
					escribir[2] = tablero[cont_der].get_num1();// numero en la drcha
				}
				for (int i = 0; i <= 6; i++) {
					escribir[3 + (2 * i)] = jugadores[turno].get_ficha(i).get_num1();
					escribir[4 + (2 * i)] = jugadores[turno].get_ficha(i).get_num2();
				}
				
				if (eleccion == 1 && eleccion_ficha != 0 && eleccion_lado != 0) {
					escribir[0] = eleccion_final(eleccion_ficha, eleccion_lado);
					colocar_ficha();
				}
				else if (eleccion == 2)
					cambio_turno();

				archivo.open("py/communication_files/Jugador.txt", ios::out); //sobreescribe los datos que esten en el archivo
				if (archivo.is_open()) {
					for (int j = 0; j <= 16; j++) { //se escriben 16 numeros en el archivo
						archivo << escribir[j];
						if (j <= 15) archivo << ",";
					}
					archivo.close();  // Cerrar el archivo
				}
			}
			else if (turno != 0) { // El jugador máquina juega solo
				if (tablero[cont_izq].get_lado() == 0) {
					escribir[0] = tablero[cont_izq].get_num1();// numero en la izq 
				}
				else if (tablero[cont_izq].get_lado() == 1) {
					escribir[0] = tablero[cont_izq].get_num2(); // numero en la izq 
				}
				if (tablero[cont_der].get_lado() == 0) {
					escribir[1] = tablero[cont_der].get_num2();// numero en la drcha
				}
				else if (tablero[cont_der].get_lado() == 1) {
					escribir[1] = tablero[cont_der].get_num1();// numero en la drcha
				}
				for (int i = 0; i <= 6; i++) {
					escribir[2 + (2 * i)] = jugadores[turno].get_ficha(i).get_num1();
					escribir[3 + (2 * i)] = jugadores[turno].get_ficha(i).get_num2();
				}

				archivo.open("py/communication_files/info.txt", ios::out); // Sobre escribe los datos que esten en el archivo
				if (archivo.is_open()) {
					for (int j = 0; j <= 15; j++) { // Se escriben 16 numeros en el archivo
						archivo << escribir[j];
						if (j <= 14) archivo << ",";
					}
					archivo.close();  // Cerrar el archivo
				}

				this->jugadores[turno].juego_IA(tablero, cont_der, cont_izq, &eleccion, &eleccion_ficha, &eleccion_lado, dificultad);
				if (eleccion == 1)
					colocar_ficha();
				else if (eleccion == 2)
					cambio_turno();
				Sleep(2000); // Ponemos un sleep para "simular" el tiempo que tarda en pensar
			}
		}
	}
}

void Tablero::cambio_turno() {
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
	turno = (turno + 1) % 4;
}


void Tablero::colocar_ficha() {
	if (eleccion_lado == 1) { // Ponemos por la derecha
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if(fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
	}
	if (eleccion_lado == 2) { // Ponemos por la izquierda
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
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
				return; // Si algún jugador, que no sea el que tiene el turno, puede poner, entonces la partida continua
		}
	}
	fin = 1;
	return;
}

void Tablero::control_Raton(int x, int y) {
	if (turno == 0 && primer_movimiento == 1 && fin == 0 && movimiento_controlado == 1) {
		if (eleccion == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq) == 1) {
				eleccion = 1; // Poner
				play("bin/sonidos/seleccion_ficha.wav");
			}
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475) {
				movimiento_controlado = 0;
				eleccion = 2; // Pasar
				play("bin/sonidos/select.wav");
			}
		}
		else if (eleccion != 0 && eleccion_ficha == 0) {
			if (x >= 282 && x <= 311 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 1) != 0 && jugadores[0].get_contador() >= 0) {
				eleccion_ficha = 1;
				play("bin/sonidos/1.wav");
			}
			else if (x >= 337 && x <= 364 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 2) != 0 && jugadores[0].get_contador() >= 1) {
				eleccion_ficha = 2;
				play("bin/sonidos/2.wav");
			}
			else if (x >= 389 && x <= 418 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 3) != 0 && jugadores[0].get_contador() >= 2) {
				eleccion_ficha = 3;
				play("bin/sonidos/3.wav");
			}
			else if (x >= 444 && x <= 471 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 4) != 0 && jugadores[0].get_contador() >= 3) {
				eleccion_ficha = 4;
				play("bin/sonidos/4.wav");
			}
			else if (x >= 497 && x <= 525 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 5) != 0 && jugadores[0].get_contador() >= 4) {
				eleccion_ficha = 5;
				play("bin/sonidos/5.wav");
			}
			else if (x >= 551 && x <= 578 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 6) != 0 && jugadores[0].get_contador() >= 5) {
				eleccion_ficha = 6;
				play("bin/sonidos/6.wav");
			}
			else if (x >= 604 && x <= 633 && y >= 545 && y <= 600 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 7) != 0 && jugadores[0].get_contador() >= 6) {
				eleccion_ficha = 7;
				play("bin/sonidos/7.wav");
			}
		}
		else if (eleccion != 0 && eleccion_ficha != 0 && eleccion_lado == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267 && ((this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 2) || (this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 3))) {
				movimiento_controlado = 0;
				eleccion_lado = 2; // Izquierda
				play("bin/sonidos/select.wav");
			}
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475 && ((this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 1) || (this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 3))) {
				movimiento_controlado = 0;
				eleccion_lado = 1; // Derecha
				play("bin/sonidos/select.wav");
			}
			else if (x < 826 || x > 991 || y < 223 || y > 475 || (y >= 267 && y <= 434)) {
				eleccion_ficha = 0;
				play("bin/sonidos/seleccion_ficha.wav");
			}
		}
	}
	// Reseteamos los valores de x e y para que no me influyan en jugadas posteriores
	x = 0;
	y = 0;
}

void Tablero::control_Gestos(GestureReader* gesto) {
	if (turno == 0 && primer_movimiento == 1 && fin == 0 && movimiento_controlado == 1) {
		if (eleccion == 0) {
			gesto->identificar_gesto();
			if (gesto->get_Gesto() == 6 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq) == 1) {
				eleccion = 1; // Poner
				play("bin/sonidos/seleccion_ficha.wav");
			}
			else if (gesto->get_Gesto() == 7) {
				eleccion = 2; // Pasar
				movimiento_controlado = 0;
				play("bin/sonidos/select.wav");
			}
		}
		else if (eleccion != 0 && eleccion_ficha == 0) {
			gesto->identificar_gesto();
			if (gesto->get_Gesto() == 1 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 1) != 0 && jugadores[0].get_contador() >= 0) {
				eleccion_ficha = 1;
				play("bin/sonidos/1.wav");
			}
			else if (gesto->get_Gesto() == 2 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 2) != 0 && jugadores[0].get_contador() >= 1) {
				eleccion_ficha = 2;
				play("bin/sonidos/2.wav");
			}
			else if (gesto->get_Gesto() == 3 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 3) != 0 && jugadores[0].get_contador() >= 2) {
				eleccion_ficha = 3;
				play("bin/sonidos/3.wav");
			}
			else if (gesto->get_Gesto() == 4 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 4) != 0 && jugadores[0].get_contador() >= 3) {
				eleccion_ficha = 4;
				play("bin/sonidos/4.wav");
			}
			else if (gesto->get_Gesto() == 5 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 5) != 0 && jugadores[0].get_contador() >= 4) {
				eleccion_ficha = 5;
				play("bin/sonidos/5.wav");
			}
			else if (gesto->get_Gesto() == 8 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 6) != 0 && jugadores[0].get_contador() >= 5) {
				eleccion_ficha = 6;
				play("bin/sonidos/6.wav");
			}
			else if (gesto->get_Gesto() == 9 && this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, 7) != 0 && jugadores[0].get_contador() >= 6) {
				eleccion_ficha = 7;
				play("bin/sonidos/7.wav");
			}
			else if (gesto->get_Gesto() == 0) {
				eleccion = 0;
				play("bin/sonidos/select.wav");
			}
		}
		else if (eleccion != 0 && eleccion_ficha != 0 && eleccion_lado == 0) {
			gesto->identificar_gesto();
			if (gesto->get_Gesto() == 6 && ((this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 2) || (this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 3))) {
				eleccion_lado = 2; // Izquierda
				movimiento_controlado = 0;
				play("bin/sonidos/select.wav");
			}
			else if (gesto->get_Gesto() == 7 && ((this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 1) || (this->jugadores[turno].posibilidad_poner(tablero, cont_der, cont_izq, eleccion_ficha) == 3))) {
				eleccion_lado = 1; // Derecha
				movimiento_controlado = 0;
				play("bin/sonidos/select.wav");
			}
			else if (gesto->get_Gesto() == 0) {
				eleccion_ficha = 0;
				play("bin/sonidos/seleccion_ficha.wav");
			}
		}
	}
}

void Tablero::partida_nueva() {
	primer_movimiento = 0;
	movimiento_controlado = 0;
	inicio = 0;
	fin = 0;
	sonido_final = 0;
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
	turno = -1;
	cont_der = 27;
	cont_izq = 27;
	for (int i = 0; i < 55; i++)
		tablero[i].cambiar_ficha();
	for (int i = 0; i < 4; i++)
		this->jugadores[i].vaciar_contenido();
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
	// Otorgamos el turno al que tenga la ficha más alta, el 6 doble, de identificador 28
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (this->jugadores[i].get_ficha(j).get_id() == 28) {
				turno = i;
				return;
			}
		}
	}
}

// Esta función determina quien tiene la ficha más alta y empieza a jugar
void Tablero::primer_turno() {
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 7; j++) {
			if (this->jugadores[i].get_ficha(j).get_id() == 28) {
				tablero[27].cambiar_ficha(28); // Coloca la ficha en el tablero
				this->jugadores[i].cambiar_ficha(j); // le quita la ficha al jugador
				return;
			}
		}
	}
}

void Tablero::dibuja(int* modo) {
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
	if (turno == 0 && fin == 0)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno1.png").id);
	else if (turno == 0 && fin == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Ganador1.png").id);
	else if (turno == 1 && fin == 0)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno2.png").id);
	else if (turno == 1 && fin == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Ganador2.png").id);
	else if (turno == 2 && fin == 0)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno3.png").id);
	else if (turno == 2 && fin == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Ganador3.png").id);
	else if (turno == 3 && fin == 0)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Turno4.png").id);
	else if (turno == 3 && fin == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Ganador4.png").id);
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
	if (turno == 0 && primer_movimiento == 1 && fin == 0 && movimiento_controlado == 1) {
		if (eleccion == 0 && *modo == 1)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Poner-Pasar_raton.png").id);
		else if (eleccion == 0 && *modo == 2)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Poner-Pasar_gestos.png").id);
		else if (eleccion_ficha == 0 && *modo == 1)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/negro.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 6)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_7.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 5)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_6.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 4)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_5.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 3)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_4.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 2)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_3.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 1)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_2.png").id);
		else if (eleccion_ficha == 0 && *modo == 2 && jugadores[0].get_contador() == 0)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichas_gestos_1.png").id);
		else if (eleccion_lado == 0 && *modo == 1)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Izq-Dcha_raton.png").id);
		else if (eleccion_lado == 0 && *modo == 2)
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/Izq-Dcha_gestos.png").id);
	}
	else if (fin == 1 && *modo == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/volver_menu_raton.png").id);
	else if (fin == 1 && *modo == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/volver_menu_gestos.png").id);
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

	// Dibujamos un borde rojo sobre la ficha elegida
	if (eleccion_ficha != 0 && turno == 0 && fin == 0) {
		glBegin(GL_POLYGON);
		glColor3ub(255, 0, 0);
		glVertex3f(8.7 + 2.7 * (eleccion_ficha - 1), 6.2, 0.9);
		glVertex3f(10.8 + 2.7 * (eleccion_ficha - 1), 6.2, 0.9);
		glVertex3f(10.8 + 2.7 * (eleccion_ficha - 1), 9.8, 0.9);
		glVertex3f(8.7 + 2.7 * (eleccion_ficha - 1), 9.8, 0.9);
		glEnd();
	}

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
			else if (i >= 53 && i < 55) {
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

	// Esto sirve para que el sonido de victoria suene de forma síncrona con la actualización de la pantalla
	if (fin == 1 && sonido_final == 0) {
		play("bin/sonidos/win.wav");
		sonido_final = 1;
	}
	// Al igual que en el if anterior, el usuario puede empezar a seleccionar en el momento en el que se actualiza la pantalla con el jugador 1 jugando
	if (turno == 0 && primer_movimiento == 1 && eleccion == 0 && eleccion_ficha == 0 && eleccion_lado == 0 && movimiento_controlado == 0) {
		play("bin/sonidos/turno.wav");
		movimiento_controlado = 1;
	}
}

int Tablero::eleccion_final(int posicion, int lugar)
{
	bool tableroo;//true si es IZQ, false si es DRCHA
	if (lugar == 1) tableroo = FALSE;
	else tableroo = TRUE;

	switch (posicion)
	{
		case 0:
			return 0;
			break;
		case 1:
			if (tableroo) return 1;
			else return 8;
			break;
		case 2:
			if (tableroo) return 2;
			else return 9;
			break;
		case 3:
			if (tableroo) return 3;
			else return 10;
			break;
		case 4:
			if (tableroo) return 4;
			else return 11;
			break;
		case 5:
			if (tableroo) return 5;
			else return 12;
			break;
		case 6:
			if (tableroo) return 6;
			else return 13;
			break;
		case 7:
			if (tableroo) return 7;
			else return 14;
			break;
		default:
			return 0;
			break;
	}
}