#include "Coordinador.h"

Coordinador::Coordinador() {
	modo = 2; // 1 raton, 2 gestos
	estado = MENU;
}

Coordinador::~Coordinador() {}

void Coordinador::control_Raton(int x, int y) {
	if (estado == MENU) {
		if (x >= 100 && x <= 900 && y >= 350 && y <= 550) {
			estado = OPCIONES;
			play("bin/sonidos/success.wav");
		}
		else if (x >= 900 && x <= 997 && y >= 592 && y <= 679) {
			estado = INSTRUCCIONES;
			play("bin/sonidos/success.wav");
		}
	}
	else if (estado == INSTRUCCIONES) {
		if (x >= 878 && x <= 984 && y >= 319 && y <= 389) {
			estado = MENU;
			play("bin/sonidos/success.wav");
		}
	}
	else if (estado == OPCIONES) {
		if (x >= 180 && x <= 345 && y >= 382 && y <= 450) {
			dificultad = 1;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (x >= 607 && x <= 773 && y >= 382 && y <= 450) {
			dificultad = 2;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (x >= 180 && x <= 345 && y >= 561 && y <= 627) {
			dificultad = 3;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (x >= 607 && x <= 773 && y >= 561 && y <= 627) {
			dificultad = 4;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
	}
	else if (estado == JUEGO && tablero.get_final() == 0)
		tablero.control_Raton(x, y);
	else if (estado == JUEGO && tablero.get_final() == 1) {
		if (x >= 832 && x <= 983 && y >= 286 && y <= 351) {
			estado = MENU;
			play("bin/sonidos/success.wav");
		}
	}
	// Reseteamos los valores de x e y para que no me influyan en jugadas posteriores
	x = 0;
	y = 0;
}

void Coordinador::control_Gestos() {
	if (estado == MENU) {
		gesto.identificar_gesto();
		if (gesto.get_Gesto() == 5) {
			estado = OPCIONES;
			play("bin/sonidos/success.wav");
		}
		else if (gesto.get_Gesto() == 7) {
			estado = INSTRUCCIONES;
			play("bin/sonidos/success.wav");
		}
		else if (gesto.get_Gesto() == 0)
			exit(1);
	}
	else if (estado == INSTRUCCIONES) {
		gesto.identificar_gesto();
		if (gesto.get_Gesto() == 5) {
			estado = MENU;
			play("bin/sonidos/success.wav");
		}
	}
	else if (estado == OPCIONES) {
		gesto.identificar_gesto();
		if (gesto.get_Gesto() == 1) {
			dificultad = 1;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (gesto.get_Gesto() == 2) {
			dificultad = 2;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (gesto.get_Gesto() == 3) {
			dificultad = 3;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
		else if (gesto.get_Gesto() == 4) {
			dificultad = 4;
			tablero.partida_nueva();
			estado = JUEGO;
			play("bin/sonidos/success.wav");
		}
	}
	else if (estado == JUEGO && tablero.get_final() == 0)
		tablero.control_Gestos(&gesto);
	else if (estado == JUEGO && tablero.get_final() == 1) {
		gesto.identificar_gesto();
		if (gesto.get_Gesto() == 0) {
			estado = MENU;
			play("bin/sonidos/success.wav");
		}
	}		
}

void Coordinador::partida() {
	if (estado == JUEGO)
		tablero.partida(dificultad);
}

void Coordinador::dibuja() {
	gluLookAt(20, 20, 53,  // posicion del ojo
		20, 20, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y)
	if (estado == MENU || estado == INSTRUCCIONES || estado == OPCIONES)
		dibuja_Menu();
	else if (estado == JUEGO)
		tablero.dibuja(&modo);
}

void Coordinador::dibuja_Menu() {
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	if (estado == MENU && modo == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/menu_raton.png").id);
	else if (estado == MENU && modo == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/menu_gestos.png").id);
	else if (estado == INSTRUCCIONES && modo == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/instrucciones_raton.png").id);
	else if (estado == INSTRUCCIONES && modo == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/instrucciones_gestos.png").id);
	else if (estado == OPCIONES && modo == 1)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/dificultad_raton.png").id);
	else if (estado == OPCIONES && modo == 2)
		glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/dificultad_gestos.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-6, 0, 0);
	glTexCoord2d(1, 1);		glVertex3f(46, 0, 0);
	glTexCoord2d(1, 0);		glVertex3f(46, 40, 0);
	glTexCoord2d(0, 0);		glVertex3f(-6, 40, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}