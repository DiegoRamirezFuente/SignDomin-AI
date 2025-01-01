#include "Coordinador.h"
#include <windows.h>

Coordinador domino;
void OnDraw(void); // Esta funcion sera llamada para dibujar
void OnTimer(int value); // Esta funcion sera llamada cuando transcurra una temporizacion
void clickraton(int boton, int estado, int x, int y); // Clik de la posicion

// El thread ejecuta la función que enlaza con Python
void runPython() {
	if (system("python \"../Domino/py/gestures.py\"") != 0)
		exit(-1);
}

// El thread 2 ejecuta la función que controla el movimiento del jugador
void control_juego() {
	if (domino.get_Modo() == 1)
		glutMouseFunc(clickraton);
	else {
		while (1)
			domino.control_Gestos();
	}
}

int main(int argc, char* argv[]){
	
	//HWND hwnd = GetConsoleWindow(); // Obtén el manejador de la ventana de consola
	//ShowWindow(hwnd, SW_HIDE);     // Oculta la ventana
	
	thread py(runPython);
	
	// Antes de comenzar con el desarrollo del juego, inicializamos el gestor de ventanas GLUT y creamos la ventana
	glutInit(&argc, argv);
	glutInitWindowSize(1000, 700);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
	glutCreateWindow("Juego del Domino");

	// También, tenemos que habilitar luces y definir perspectiva
	glEnable(GL_LIGHT0);
	glEnable(GL_LIGHTING);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);
	glMatrixMode(GL_PROJECTION);
	gluPerspective(40.0, 800 / 600.0f, 0.1, 150);

	// Registrar los callbacks
	glutDisplayFunc(OnDraw);
	glutTimerFunc(25, OnTimer, 0);
	thread control(control_juego);
	
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();
	printf("Ventana cerrada");
	return 0;
}

void OnDraw(void)
{
	//Borrado de la pantalla	
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Para definir el punto de vista
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	domino.dibuja();

	//no borrar esta linea ni poner nada despues
	glutSwapBuffers();
}

void OnTimer(int value) {
	domino.partida();
	//no borrar estas lineas
	glutTimerFunc(25, OnTimer, 0);
	glutPostRedisplay();
}

void clickraton(int boton, int estado, int x, int y) { // sirve para controlar el juego por ratón
	if (boton == GLUT_LEFT_BUTTON && estado == GLUT_DOWN) {
		domino.control_Raton(x, y);
		glutPostRedisplay();
	}
}