#include "Coordinador.h"
#include <thread>

Coordinador domino;
int jugadores = 0, dificultad = 0;

// los callback, funciones que seran llamadas automaticamente por la glut
// cuando sucedan eventos
// NO HACE FALTA LLAMARLAS EXPLICITAMENTE
void OnDraw(void); // esta funcion sera llamada para dibujar
void OnTimer(int value); // esta funcion sera llamada cuando transcurra una temporizacion
void clickraton(int boton, int estado, int x, int y); // Clik de la posicion
void doGesture();
void runPython() {
	int result = system("python \"../Domino/py/gestures.py\"");
	if (result != 0) {
		std::cerr << "Error al ejecutar el script de Python." << std::endl;
	}
}
int main(int argc, char* argv[]){

	std::thread pyThread(runPython);
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
	glutTimerFunc(25, OnTimer, 0); //le decimos que dentro de 25ms llame 1 vez a la funcion OnTimer()
	glutMouseFunc(clickraton);
	std::thread gesture(doGesture);
	//pasarle el control a GLUT,que llamara a los callbacks
	glutMainLoop();
	gesture.join();
	pyThread.join();
	
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
void doGesture() {
	domino.control_gesto();
	
}