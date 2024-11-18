#pragma once
#include "Ficha.h" // Para incluir todas las librerias necesarias

class GestureReader {
private:
    int gesto; // Variable para almacenar el gesto reconocido
    const string filepath = "py/communication.txt"; // Ruta al archivo de comunicaci�n
    void clearFile(); // M�todo privado para limpiar el contenido del archivo
    bool isFileModified(); // M�todo privado para verificar si el archivo ha sido modificado
public:
    GestureReader();
    void identificar_gesto(); // M�todo para obtener el gesto desde el archivo
    int get_Gesto() { return gesto; }
};