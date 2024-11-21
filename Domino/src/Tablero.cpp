#include "Tablero.h"


Tablero::Tablero() {
	primer_movimiento = 0;
	turno = -1;
	turno_desfasado = 0;
	inicio = 0;
	fin = 0;
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
	cont_der = 27;
	cont_izq = 27;

}

void Tablero::partida(int dificultad) {
	int posibilidad_total = 0;
	int posibilidad_ficha = 0;
	Ficha aux; //Para saber que ficha se ha jugado
	Ficha aux2; // para saber que numeros estan disponibles en el tablero

	aux2.default_id();

	if (inicio == 0) {
		inicio = 1;
		reparto_fichas();
		//Sleep(2000);
	}
	else if (inicio == 1) {
		inicio = 2;
		primer_turno();
		//Sleep(2000);
	}
	else {
		inicio++;
		cout << "RONDA           " << inicio - 1 << endl;


		if (fin == 0) {
			if (turno == -1) { // Nosotros controlamos el jugador local (no quiero que juege ningun jugador local cambio turno a -1)(antes estaba en0)
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
				//if (turno == 0) {
				// inicio - 3 es cuando se empieza a jugar desde el segundo turno, es decir en el segundo turno es 0
				//ESTO IMPLICA QUE SE EMPIEZAN A TOMAR DATOS EN EL SEGUNDO TURNO, EL PRIMER TURNO ES AUTOMATICO EMPEZANDO EL QUE TENGA LA FICHA 6/6
				if (((inicio - 3) % 4)==0) veces_jugadas++;
				Turno_jugador[turno][veces_jugadas] = veces_jugadas;
				cout << "el turno del jugador " << turno + 1 << "es (cantidad de veces que ha jugado una ficha o ha pasado turno): [" << turno << "][" << veces_jugadas << "] (0 primer turno) " << Turno_jugador[turno][veces_jugadas] << endl;
				turno_desfasado = turno;
				cout << inicio - 3 << " veces que ha jugado el jugador " << turno + 1 << ": " << veces_jugadas << endl;

					if (tablero[cont_izq].get_lado() == 0) { aux2.set_num1(tablero[cont_izq].get_num1());// cout << "0 FICHA EN izq " << tablero[cont_izq].get_num1() << endl; 
					}
					else if (tablero[cont_izq].get_lado() == 1) { aux2.set_num1(tablero[cont_izq].get_num2()); //cout << "1 FICHA EN izq " << tablero[cont_izq].get_num2() << endl;
					}
					if (tablero[cont_der].get_lado() == 0) { aux2.set_num2(tablero[cont_der].get_num2());// cout << "0 FICHA EN der " << tablero[cont_der].get_num2() << endl;
					}
					else if (tablero[cont_der].get_lado() == 1) { aux2.set_num2(tablero[cont_der].get_num1());// cout << "1 FICHA EN der " << tablero[cont_der].get_num1() << endl; 
					}

					cout <<endl<< turno<<" "<< veces_jugadas << endl;
					//Tablero_turno[turno].push_back(aux); //guarda, cada turno, que numero en izq (num1) esta disponible y lo mismo con la derecha (num2)

					Tablero_turno[turno][veces_jugadas].set_num1(aux2.get_num1());
					Tablero_turno[turno][veces_jugadas].set_num2(aux2.get_num2());

					cout << "--->["<<turno<<"]["<< veces_jugadas << "] ----> IZQ " << Tablero_turno[turno][veces_jugadas].get_num1() << "  DRCHA  " << Tablero_turno[turno][veces_jugadas].get_num2() << endl;

					cout << "FICHAS DEL JUGADOR NUMERO " << turno + 1 << endl;
					for (int i = 0; i <= 6; i++) {
						Ficha auxFicha = jugadores[turno].get_ficha(i);
						//Mano_jugador[turno][veces_jugadas].push_back(auxFicha);
						Mano_jugador[turno][veces_jugadas][i].set_num1(auxFicha.get_num1());
						Mano_jugador[turno][veces_jugadas][i].set_num2(auxFicha.get_num2());
						//cout << "FICHA  " << i + 1 << " num1 " << auxFicha.get_num1() << endl;
						//cout << "FICHA  " << i + 1 << " num2 " << auxFicha.get_num2() << endl;
						cout << "FICHA vector [" << turno << "][" << veces_jugadas << "]["<< i << "] num1 " << Mano_jugador[turno][veces_jugadas][i].get_num1() << endl;
						cout << "FICHA vector [" << turno << "][" << veces_jugadas << "]["<< i << "] num2 " << Mano_jugador[turno][veces_jugadas][i].get_num2() << endl;
					}
				//}
				this->jugadores[turno].juego_IA(tablero, cont_der, cont_izq, &eleccion, &eleccion_ficha, &eleccion_lado, dificultad);
				cout << "ficha seleccionada: " << eleccion_ficha << " en el lado: " << eleccion_lado << endl;//eleccion_lado=1--> DRCHA ; 2--->IZQ
				ficha_puesta = eleccion_final(eleccion_ficha, eleccion_lado);
				seleccion_absoluta[turno][veces_jugadas] = ficha_puesta;
				cout << "la ficha que tengo que poner es la: " << ficha_puesta << endl;
				if (eleccion == 1)
					aux=colocar_ficha();
				if (eleccion == 2){
					cambio_turno();
					aux.default_id();
				}
				//Sleep(5000); // Ponemos un sleep para "simular" el tiempo que tarda en pensar //NO HAY QUE ESPERAR
				//for (int i = 0; i < size(tablero); i++) {
					//cout <<"TABLERO    " << tablero << "     FIN" << endl;

				// }

			}
		}
		else {
			cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
			cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
			cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
			cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
			cout << "El jugador " << turno + 1 << " ha ganado la partida" << endl;
			archivo.open("datos.csv", ios::app);
			//archivo << "ganador jugador numero: " << turno + 1 << " ; " << "num1 ficha jugada ; " << "num2 ficha jugada ; " << "Turno del jugador ; " << "tablero IZQ ; " << "TABLERO DRCHA" << endl;
			//for (int j = 0; j <= 6; j++) {
			//	archivo << "ficha " << j << " numero 1 " << ";" << "ficha " << j << " numero 2 " << ";";
			//}
			//archivo << endl;
			for (int i = 1; i <= veces_jugadas; i++) {
				archivo << seleccion_absoluta[turno][i] << "," << Tablero_turno[turno][i].get_num1() << Tablero_turno[turno][i].get_num2();
				for (int j = 0; j <= 6; j++) {
					archivo << "," << Mano_jugador[turno][i][j].get_num1() << Mano_jugador[turno][i][j].get_num2();
				}
				archivo << endl;
			}
			archivo.close();
			//if (turno + 1 == 0) { cout << "ha ganado el jugador indicado" << endl; cout << "ha ganado el jugador indicado" << endl; cout << "ha ganado el jugador indicado" << endl;}
			exit(1); // para salir cuando termine 
		}
	}
	//if (turno == 1) {

		cout << endl <<"FICHA PUESTA POR JUGADOR : "<< turno_desfasado<<" con id: " << aux.get_id() << ": num1: " << aux.get_num1() << " num2: " << aux.get_num2() << endl;
		Ficha_jugada[turno_desfasado][veces_jugadas].set_num1(aux.get_num1());
		Ficha_jugada[turno_desfasado][veces_jugadas].set_num2(aux.get_num2());
		cout << "FICHA PUESTA [" << turno_desfasado << "][" << veces_jugadas << "] ----> NUM1 " << Ficha_jugada[turno_desfasado][veces_jugadas].get_num1() << "  NUM2  " << Ficha_jugada[turno_desfasado][veces_jugadas].get_num2() << endl;
		cout << endl;
		turno_desfasado = (turno_desfasado + 1) % 4;
	//}
	//archivo.open("datos.csv", ios::app);

	//archivo << "RONDA" << ";"<< inicio - 1 << endl;

	//archivo.close();

}

void Tablero::cambio_turno() {
	turno = (turno + 1) % 4;
	eleccion = 0;
	eleccion_ficha = 0;
	eleccion_lado = 0;
}

Ficha Tablero::colocar_ficha() {
	if (eleccion_lado == 1) { // Ponemos por la derecha
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if(fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_der].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num2()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_der].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_der].get_num1()) {
			tablero[++cont_der].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
	}
	if (eleccion_lado == 2) { // Ponemos por la izquierda
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_izq].get_lado() == 0 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num1()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num1() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id(), 1);
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
		}
		if (tablero[cont_izq].get_lado() == 1 && this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_num2() == tablero[cont_izq].get_num2()) {
			tablero[--cont_izq].cambiar_ficha(this->jugadores[turno].get_ficha(eleccion_ficha - 1).get_id());
			Ficha eleccion = this->jugadores[turno].get_ficha(eleccion_ficha - 1);
			this->jugadores[turno].cambiar_ficha(eleccion_ficha - 1);
			final_partida();
			if (fin == 0)
				cambio_turno();
			return eleccion;
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
	if (turno == 0 && primer_movimiento == 1) {
		if (eleccion == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267)
				eleccion = 1;
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475)
				eleccion = 2;
		}
		else if (eleccion != 0 && eleccion_ficha == 0) {
			if (x >= 282 && x <= 311 && y >= 545 && y <= 600)
				eleccion_ficha = 1;
			else if (x >= 337 && x <= 364 && y >= 545 && y <= 600)
				eleccion_ficha = 2;
			else if (x >= 389 && x <= 418 && y >= 545 && y <= 600)
				eleccion_ficha = 3;
			else if (x >= 444 && x <= 471 && y >= 545 && y <= 600)
				eleccion_ficha = 4;
			else if (x >= 497 && x <= 525 && y >= 545 && y <= 600)
				eleccion_ficha = 5;
			else if (x >= 551 && x <= 578 && y >= 545 && y <= 600)
				eleccion_ficha = 6;
			else if (x >= 604 && x <= 633 && y >= 545 && y <= 600)
				eleccion_ficha = 7;
			else
				eleccion = 0;
		}
		else if (eleccion != 0 && eleccion_ficha != 0 && eleccion_lado == 0) {
			if (x >= 826 && x <= 991 && y >= 223 && y <= 267)
				eleccion_lado = 2;
			else if (x >= 826 && x <= 991 && y >= 434 && y <= 475)
				eleccion_lado = 1;
			else 
				eleccion_ficha = 0;
		}

		// Reseteamos los valores de x e y para que no me influyan en clicks o jugadas posteriores
		x = 0;
		y = 0;
	}
}

void Tablero::partida_nueva() {
	primer_movimiento = 0;
	inicio = 0;
	fin = 0;
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
	for (int i = 0; i < 7; i++) {
		if (this->jugadores[0].get_ficha(i).get_id() == 28) {
			turno = 0; // El turno del jugador 1 lo simbolizo con el numero 0
			return;
		}
		else if (this->jugadores[1].get_ficha(i).get_id() == 28) {
			turno = 1; // El turno del jugador 2 lo simbolizo con el numero 1
			return;
		}
		else if (this->jugadores[2].get_ficha(i).get_id() == 28) {
			turno = 2; // El turno del jugador 3 lo simbolizo con el numero 2
			return;
		}
		else if (this->jugadores[3].get_ficha(i).get_id() == 28) {
			turno = 3; // El turno del jugador 4 lo simbolizo con el numero 3
			return;
		}
	}
}

// Esta función determina quien tiene la ficha más alta y empieza a jugar
void Tablero::primer_turno() {
	primer_movimiento = 1;
	cambio_turno();
	turno_desfasado = (turno_desfasado + 1) % 4;
	for (int i = 0; i < 7; i++) {
		if (this->jugadores[0].get_ficha(i).get_id() == 28) {
			tablero[27].cambiar_ficha(28); // Coloca la ficha en el tablero
			this->jugadores[0].cambiar_ficha(i); // le quita la ficha al jugador
			return;
		}
		if (this->jugadores[1].get_ficha(i).get_id() == 28) {
			tablero[27].cambiar_ficha(28);
			this->jugadores[1].cambiar_ficha(i);
			return;
		}
		if (this->jugadores[2].get_ficha(i).get_id() == 28) {
			tablero[27].cambiar_ficha(28);
			this->jugadores[2].cambiar_ficha(i);
			return;
		}
		if (this->jugadores[3].get_ficha(i).get_id() == 28) {
			tablero[27].cambiar_ficha(28);
			this->jugadores[3].cambiar_ficha(i);
			return;
		}
	}
}

int Tablero::eleccion_final(int posicion, int lugar)
{
	bool tableroo;//true si es IZQ, false si es DRCHA
	if (lugar == 1) tableroo = FALSE;
	else tableroo = TRUE;
	//else if (lugar == 2) tablero = TRUE;
	if (tableroo) cout << "TABLERO --> TRUE" << " EL LUGAR ES: " << lugar << endl;
	else cout << "TABLERO --> FALSE" << " EL LUGAR ES: " << lugar << endl;
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

void Tablero::dibuja() {
	gluLookAt(20, 20, 53,  // posicion del ojo
		20, 20, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y)

	// Pintamos el tablero
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/tablero.png").id);
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
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Turno1.png").id);
	else if (turno == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Turno2.png").id);
	else if (turno == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Turno3.png").id);
	else if (turno == 3)
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Turno4.png").id);
	else
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/negro.png").id);
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
	if (turno == 0 && primer_movimiento == 1) {
		if (eleccion == 0)
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Poner-Pasar.png").id);
		else if (eleccion_ficha == 0)
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/negro.png").id);
		else
			glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/Izq-Dcha.png").id);
	}
	else
		glBindTexture(GL_TEXTURE_2D, getTexture("imagenes/negro.png").id);
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