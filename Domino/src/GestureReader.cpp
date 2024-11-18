#include "GestureReader.h"

GestureReader::GestureReader() {
    gesto = -1;
    clearFile();
}

void GestureReader::clearFile() {
    ofstream clearFile(filepath, ofstream::trunc); // vacio el archivo
    clearFile.close(); // cierro el archivo
}

bool GestureReader::isFileModified() {
    struct stat fileInfo; // Sirve para saber si el archivo ha sido modificado por Python
    // Llama a stat para obtener informaci�n del archivo
    if (stat(filepath.c_str(), &fileInfo) == 0) {
        // Creamos una variable static que conserva su valor entre llamadas sucesivas al m�todo
        static time_t lastModified = fileInfo.st_mtime; // Solo se ejecuta la primera vez
        // Compara la fecha de modificaci�n actual con la �ltima conocida
        if (fileInfo.st_mtime != lastModified) {
            lastModified = fileInfo.st_mtime; // Actualiza la �ltima fecha conocida
            return true; // Devuelve true si el archivo si fue modificado
        }
    }
    return false; // Devuelve false si el archivo no fue modificado
}

void GestureReader::identificar_gesto() {
    gesto = -1;
    clearFile();
    while (gesto == -1) {
        if (isFileModified()) {
            ifstream file(filepath); // Abre el archivo en modo lectura
            if (file.is_open()) {
                string line;
                getline(file, line); // Lee la primera l�nea del archivo
                file.close(); // Cierra el archivo despu�s de leer
                if (!line.empty()) {
                    try {
                        gesto = stoi(line); // Convertimos la l�nea le�da a un n�mero entero
                        clearFile();  // Limpia el archivo despu�s de leer el gesto
                    }
                    catch (const invalid_argument& e) { // Error de conversi�n
                        cout << "Error de conversi�n: " << e.what() << endl;
                    }
                }
            }
        }
        if (gesto == -1) {
            this_thread::sleep_for(std::chrono::milliseconds(50)); 
        }
    }
}