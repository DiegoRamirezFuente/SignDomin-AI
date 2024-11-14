#include "Coordinador.h"
#include "ETSIDI.h"

GestureReader g_coord;

Coordinador::Coordinador() {
	dificultad = 1;
	final_partida = 0;
	estado = MENU;
}

Coordinador::~Coordinador() {}

/*void Coordinador::control_Raton(int x, int y) {
	if (estado == MENU) {
		if (x >= 100 && x <= 900 && y >= 350 && y <= 550) {
			x = 0;
			y = 0;
			//tablero.partida_nueva();
			//estado = JUEGO;
		}
	}
	if (estado == JUEGO) {
		//tablero.control_Raton(x, y);
		tablero.control_gesto();
	}
	
}*/
void Coordinador::control_gesto() {
	int gesto;
	if (estado == MENU) {
		do {
			gesto = g_coord.get_gesture();
		} while (gesto != 5 && gesto != 0);
		if (gesto == 5) {
			printf("Palma detectada");
			ETSIDI::play("bin/sounds/success.wav");
			tablero.partida_nueva();
			estado = JUEGO;
		}
		else if (gesto == 0) {
			printf("Bye bye");
			exit(1);
		}
		if (estado == JUEGO) 
			tablero.control_gesto();

		}
	}


void Coordinador::partida() {
	if (estado == MENU) {
		final_partida = 0;
		
	}
	if (estado == JUEGO && final_partida == 0)
		tablero.partida(dificultad);
}

void Coordinador::dibuja() {
	if (estado == MENU)
		dibuja_Menu();
	if (estado == INSTRUCCIONES)
		dibuja_Instrucciones();
	if (estado == JUEGO)
		tablero.dibuja();
}

void Coordinador::dibuja_Menu() {
	gluLookAt(20, 20, 53,  // posicion del ojo
		20, 20, 0,      // hacia que punto mira  (0,0,0) 
		0.0, 1.0, 0);      // definimos hacia arriba (eje Y) 
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/menu.png").id);
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

void Coordinador::dibuja_Instrucciones() {
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, ETSIDI::getTexture("bin/imagenes/menu.png").id);
	glDisable(GL_LIGHTING);
	glBegin(GL_POLYGON);
	glColor3f(1, 1, 1);
	glTexCoord2d(0, 1);		glVertex3f(-15, 38, 0);
	glTexCoord2d(1, 1);		glVertex3f(47, 38, 0);
	glTexCoord2d(1, 0);		glVertex3f(47, 46, 0);
	glTexCoord2d(0, 0);		glVertex3f(-15, 46, 0);
	glEnd();
	glEnable(GL_LIGHTING);
	glDisable(GL_TEXTURE_2D);
}