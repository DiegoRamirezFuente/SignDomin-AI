// main.cpp
#include <wx/wx.h>
#include "Menu.h" // Asegúrate de que el archivo header se llame Menu.h o el nombre correcto

class MyApp : public wxApp {
public:
    virtual bool OnInit() {
        SignDominAI* frame = new SignDominAI(nullptr, wxID_ANY, _("SignDomin-AI"));
        frame->Show(true);
        return true;
    }
};

wxIMPLEMENT_APP(MyApp);
