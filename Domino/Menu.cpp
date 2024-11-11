///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#include "Menu.h"
#include <wx/msgdlg.h>  // Incluye esta cabecera para usar wxMessageBox

///////////////////////////////////////////////////////////////////////////

SignDominAI::SignDominAI(wxWindow* parent, wxWindowID id, const wxString& title, const wxPoint& pos, const wxSize& size, long style) : wxFrame(parent, id, title, pos, size, style)
{
	this->SetSizeHints(wxDefaultSize, wxDefaultSize);
	this->SetBackgroundColour(wxColour(30, 0, 78));

	wxFlexGridSizer* fgSizer2;
	fgSizer2 = new wxFlexGridSizer(3, 1, 0, 0);
	fgSizer2->SetFlexibleDirection(wxBOTH);
	fgSizer2->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_bitmap2 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("resources/menu.bmp"), wxBITMAP_TYPE_ANY), wxPoint(-1, -1), wxSize(1344, 454), 0);
	fgSizer2->Add(m_bitmap2, 1, wxALL | wxEXPAND, 5);

	m_bpButton3 = new wxBitmapButton(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(672, 134), wxBU_AUTODRAW | 0);

	m_bpButton3->SetBitmap(wxBitmap(wxT("resources/play.bmp"), wxBITMAP_TYPE_ANY));
	fgSizer2->Add(m_bpButton3, 0, wxALIGN_CENTER | wxALL, 5);

	wxFlexGridSizer* fgSizer3;
	fgSizer3 = new wxFlexGridSizer(1, 2, 0, 0);
	fgSizer3->SetFlexibleDirection(wxBOTH);
	fgSizer3->SetNonFlexibleGrowMode(wxFLEX_GROWMODE_SPECIFIED);

	m_bitmap4 = new wxStaticBitmap(this, wxID_ANY, wxBitmap(wxT("resources/name.bmp"), wxBITMAP_TYPE_ANY), wxDefaultPosition, wxSize(1210, 168), 0);
	fgSizer3->Add(m_bitmap4, 1, wxALL | wxEXPAND, 5);

	m_bpButton31 = new wxBitmapButton(this, wxID_ANY, wxNullBitmap, wxDefaultPosition, wxSize(134, 168), wxBU_AUTODRAW | 0);

	m_bpButton31->SetBitmap(wxBitmap(wxT("resources/instrucciones.bmp"), wxBITMAP_TYPE_ANY));
	fgSizer3->Add(m_bpButton31, 0, wxALL | wxEXPAND, 5);


	fgSizer2->Add(fgSizer3, 1, wxEXPAND, 5);


	this->SetSizer(fgSizer2);
	this->Layout();

	this->Centre(wxBOTH);

	// Connect Events
	m_bpButton3->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SignDominAI::PlayClick), NULL, this);
	m_bpButton31->Connect(wxEVT_COMMAND_BUTTON_CLICKED, wxCommandEventHandler(SignDominAI::ManualClick), NULL, this);
}

SignDominAI::~SignDominAI()
{
}

void SignDominAI::PlayClick(wxCommandEvent& event) {
	wxMessageBox("Botón 'Play' clicado.", "Mensaje", wxOK | wxICON_INFORMATION, this);
	event.Skip();  // Permite que el evento siga propagándose si es necesario
}

void SignDominAI::ManualClick(wxCommandEvent& event) {
	wxMessageBox("Botón 'Manual' clicado.", "Mensaje", wxOK | wxICON_INFORMATION, this);
	event.Skip();
}
