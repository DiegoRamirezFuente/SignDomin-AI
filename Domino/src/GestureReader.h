#include <string>

class GestureReader {
public:
    // Constructor que inicializa el archivo limpiándolo al comienzo
    GestureReader();

    // Método para obtener el gesto desde el archivo
    int get_gesture();

private:
    // Ruta al archivo de comunicación
    const std::string filepath = "communication.txt";

    // Método privado para limpiar el contenido del archivo
    void clearFile();

    // Método privado para verificar si el archivo ha sido modificado
    bool isFileModified();
};
