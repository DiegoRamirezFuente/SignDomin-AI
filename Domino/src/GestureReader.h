#include <string>

class GestureReader {
public:
    // Constructor que inicializa el archivo limpi�ndolo al comienzo
    GestureReader();

    // M�todo para obtener el gesto desde el archivo
    int get_gesture();

private:
    // Ruta al archivo de comunicaci�n
    const std::string filepath = "communication.txt";

    // M�todo privado para limpiar el contenido del archivo
    void clearFile();

    // M�todo privado para verificar si el archivo ha sido modificado
    bool isFileModified();
};
