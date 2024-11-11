#include <iostream>
#include "Tablero.h"
#include "Menu.h"
#include <wx/wx.h>

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        // Asegúrate de inicializar wxWidgets
        if (!wxApp::OnInit()) {
            return false;
        }

        // Crear y mostrar la ventana de SignDominAI
        SignDominAI* frame = new SignDominAI(nullptr, wxID_ANY, _("SignDomin-AI"));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP_CONSOLE(MyApp);  // Usamos wxIMPLEMENT_APP_CONSOLE para modo consola

int main(void) {
    Tablero tablero;
    int jugadores = 0, dificultad = 0;

    // Inicialización de la consola
    std::cout << "Simulador de Domino" << std::endl << std::endl;

    do {
        std::cout << "Selecciona el numero de jugadores (entre 2 y 4)" << std::endl;
        std::cout << "0: Salir del Programa" << std::endl;
        std::cin >> jugadores;
        if (jugadores == 0)
            return 0;
    } while (jugadores < 2 || jugadores > 4);

    switch (jugadores) {
    case 0:
        break;
    default:
        do {
            std::cout << std::endl << "Selecciona la dificultad:" << std::endl;
            std::cout << "1: Facil" << std::endl;
            std::cout << "2: Intermedio" << std::endl;
            std::cout << "3: Dificil" << std::endl;
            std::cout << "0: Salir del Programa" << std::endl;
            std::cin >> dificultad;
            if (dificultad == 0)
                return 0;
        } while (dificultad < 1 || dificultad > 3);

        switch (dificultad) {
        case 0:
            break;
        default:
            tablero.partida(&jugadores, &dificultad);
            break;
        }
        break;
    }

    return 0;
}
