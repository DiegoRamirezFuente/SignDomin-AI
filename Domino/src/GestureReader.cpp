#include "GestureReader.h"
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <chrono>
#include <thread>
#include <sys/stat.h>  

GestureReader::GestureReader() {
    clearFile();
}

void GestureReader::clearFile() {
    std::ofstream clearFile(filepath, std::ofstream::trunc);
    clearFile.close();
}

bool GestureReader::isFileModified() {
    struct stat fileInfo;
    if (stat(filepath.c_str(), &fileInfo) == 0) {
        static time_t lastModified = fileInfo.st_mtime;
        if (fileInfo.st_mtime != lastModified) {
            lastModified = fileInfo.st_mtime;
            return true;
        }
    }
    return false;
}

int GestureReader::get_gesture() {
    int gesture = -1;
    while (gesture == -1) {
        if (isFileModified()) {
            std::ifstream file(filepath);
            if (file.is_open()) {
                std::string line;
                std::getline(file, line);
                file.close();

                if (!line.empty()) {
                    try {
                        gesture = std::stoi(line);
                        clearFile();  // Limpiar el archivo después de leer el gesto
                    }
                    catch (const std::invalid_argument& e) {
                        std::cerr << "Error de conversión: " << e.what() << std::endl;
                    }
                }
            }
        }

        // Espera para no hacer polling constante
        if (gesture == -1) {
            std::this_thread::sleep_for(std::chrono::milliseconds(50)); // 50 ms de espera
        }
    }
    return gesture;
}
