#include "Jugador.h"

Jugador::Jugador() {
	contador = -1;
	for (int i = 0; i < 7; i++)
		fichas[i].cambiar_ficha();
}

void Jugador::vaciar_contenido() {
	contador = -1;
	for (int i = 0; i < 7; i++)
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

// Esta función devuelve un 1 si el jugador se ha quedado sin fichas
int Jugador::sin_fichas() {
	if (contador == -1)
		return 1;
	return 0;
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
	if (dificultad == 1) {
		lectura_solucion(); // Te escribe el numero del archivo en la variable numero
		if ((numero == 0 || numero == -1) && posibilidad_poner(tablero, cont_der, cont_izq) == 0) {
			*eleccion = 2;
			return;
		}
		conversion(numero);
		anti_errores(tablero, cont_der, cont_izq, eleccion, eleccion_ficha, eleccion_lado);
	}

	else if (dificultad == 2) {
		lectura_solucion(); // Te escribe el numero del archivo en la variable numero
		if (numero == 0 && posibilidad_poner(tablero, cont_der, cont_izq) == 0) {
			*eleccion = 2;
			return;
		}
		conversion(numero);
		anti_errores(tablero, cont_der, cont_izq, eleccion, eleccion_ficha, eleccion_lado);
	}
}

// Esta fu´nción sirve para detectar posibles fallos de la IA
void Jugador::anti_errores(Ficha tablero[], int cont_der, int cont_izq, int* eleccion, int* eleccion_ficha, int* eleccion_lado) {
	// En primer lugar, si la ficha escogida por la IA es correcta, no cambiamos nada
	int aux = 0;
	if (pos > 0) { // Si ha escogido poner
		aux = posibilidad_poner(tablero, cont_der, cont_izq, pos); // 0 no puede poner, 1 derecha, 2 izquierda y 3 ambas
		if (lugar == 1) { // Si ha escogido poner por la derecha
			if (aux == 1 || aux == 3) { // Si puedo poner por la derecha
				*eleccion = 1;
				*eleccion_ficha = pos;
				*eleccion_lado = lugar;
				return;
			}
			else if (aux == 2) { // Pero solo puedo poner por la izquierda
				*eleccion = 1;
				*eleccion_ficha = pos;
				*eleccion_lado = 2;
				return;
			}
		}
		else if (lugar == 2) { // Si ha escogido poner por la izquierda
			if (aux == 2 || aux == 3) { // Si puedo poner por la izquierda
				*eleccion = 1;
				*eleccion_ficha = pos;
				*eleccion_lado = lugar;
				return;
			}
			else if (aux == 1) { // Pero solo puedo poner por la derecha
				*eleccion = 1;
				*eleccion_ficha = pos;
				*eleccion_lado = 1;
				return;
			}
		}
	}

	// En caso de no poder poner esa ficha, veo si puedo poner alguna
	if (posibilidad_poner(tablero, cont_der, cont_izq) == 0) {
		*eleccion = 2; // Si no puedo, paso
		return;
	}

	// Si puede poner alguna ficha, cogemos la primera, cogemos la primera posible
	for (int i = 0; i < contador + 1; i++) {
		aux = posibilidad_poner(tablero, cont_der, cont_izq, i + 1);
		if (aux == 1 || aux == 3) { // Puede poner por la derecha
			*eleccion = 1;
			*eleccion_ficha = i + 1;
			*eleccion_lado = 1;
			return;
		}
		if (aux == 2) { // Puede poner por la izquierda
			*eleccion = 1;
			*eleccion_ficha = i + 1;
			*eleccion_lado = 2;
			return;
		}
	}
}

void Jugador::conversion(int numero) {
	// Si lugar es 2 esta a la izq, si lugar es 1 esta a la derecha
	switch (numero)
	{
	case 1:
		pos = 1;
		lugar = 2;
		break;
	case 2:
		pos = 2;
		lugar = 2;
		break;
	case 3:
		pos = 3;
		lugar = 2;
		break;
	case 4:
		pos = 4;
		lugar = 2;
		break;
	case 5:
		pos = 5;
		lugar = 2;
		break;
	case 6:
		pos = 6;
		lugar = 2;
		break;
	case 7:
		pos = 7;
		lugar = 2;
		break;
	case 8:
		pos = 1;
		lugar = 1;
		break;
	case 9:
		pos = 2;
		lugar = 1;
		break;
	case 10:
		pos = 3;
		lugar = 1;
		break;
	case 11:
		pos = 4;
		lugar = 1;
		break;
	case 12:
		pos = 5;
		lugar = 1;
		break;
	case 13:
		pos = 6;
		lugar = 1;
		break;
	case 14:
		pos = 7;
		lugar = 1;
		break;
	default:
		pos = -1;
		lugar = -1;
		break;
	}
}

void Jugador::clearFile() {
	ofstream clearFile(filepath, ofstream::trunc); // vacio el archivo
	clearFile.close(); // cierro el archivo
}

bool Jugador::isFileModified() {
	struct stat fileInfo; // Sirve para saber si el archivo ha sido modificado por Python
	// Llama a stat para obtener información del archivo
	if (stat(filepath.c_str(), &fileInfo) == 0) {
		// Creamos una variable static que conserva su valor entre llamadas sucesivas al método
		static time_t lastModified = fileInfo.st_mtime; // Solo se ejecuta la primera vez
		// Compara la fecha de modificación actual con la última conocida
		if (fileInfo.st_mtime != lastModified) {
			lastModified = fileInfo.st_mtime; // Actualiza la última fecha conocida
			return true; // Devuelve true si el archivo si fue modificado
		}
	}
	return false; // Devuelve false si el archivo no fue modificado
}

void Jugador::lectura_solucion() {
	bool lectura = false;
	while (!lectura) {
		if (isFileModified()) {
			ifstream file(filepath); // Abre el archivo en modo lectura
			if (file.is_open()) {
				string line;
				getline(file, line); // Lee la primera línea del archivo
				file.close(); // Cierra el archivo después de leer
				if (!line.empty()) {
					try {
						numero = stoi(line); // Convertimos la línea leída a un número entero
						lectura = true;
						clearFile();  // Limpia el archivo después de leer el gesto
					}
					catch (const invalid_argument& e) { // Error de conversión
						cout << "Error de conversión: " << e.what() << endl;
					}
				}
			}
		}
		else {
			this_thread::sleep_for(std::chrono::milliseconds(50)); //espera antes de volver a intentarlo
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
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichaocultavertical.png").id);
			glDisable(GL_LIGHTING);
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(20 - 2.7 * i, 35, 1);
			glTexCoord2d(1, 1);		glVertex3f(21.5 - 2.7 * i, 35, 1);
			glTexCoord2d(1, 0);		glVertex3f(21.5 - 2.7 * i, 38, 1);
			glTexCoord2d(0, 0);		glVertex3f(20 - 2.7 * i, 38, 1);
		}
		if (jugador == 2) {
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichaocultahorizontal.png").id);
			glDisable(GL_LIGHTING); 
			glBegin(GL_POLYGON);
			glColor3f(1, 1, 1);
			glTexCoord2d(0, 1);		glVertex3f(-3.5, 27.5 - 2.3 * i, 1);
			glTexCoord2d(1, 1);		glVertex3f(-0.5, 27.5 - 2.3 * i, 1);
			glTexCoord2d(1, 0);		glVertex3f(-0.5, 26 - 2.3 * i, 1);
			glTexCoord2d(0, 0);		glVertex3f(-3.5, 26 - 2.3 * i, 1);
		}
		if (jugador == 3) {
			glBindTexture(GL_TEXTURE_2D, getTexture("bin/imagenes/fichaocultahorizontal.png").id);
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