///////////////////////////////////////////////////////////////////////////
// C++ code generated with wxFormBuilder (version 4.2.1-0-g80c4cb6)
// http://www.wxformbuilder.org/
//
// PLEASE DO *NOT* EDIT THIS FILE!
///////////////////////////////////////////////////////////////////////////

#pragma once

#include <wx/artprov.h>
#include <wx/xrc/xmlres.h>
#include <wx/intl.h>
#include <wx/bitmap.h>
#include <wx/image.h>
#include <wx/icon.h>
#include <wx/statbmp.h>
#include <wx/gdicmn.h>
#include <wx/font.h>
#include <wx/colour.h>
#include <wx/settings.h>
#include <wx/string.h>
#include <wx/bmpbuttn.h>
#include <wx/button.h>
#include <wx/sizer.h>
#include <wx/frame.h>

///////////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////////////////
/// Class SignDominAI
///////////////////////////////////////////////////////////////////////////////
class SignDominAI : public wxFrame
{
private:

protected:
	wxStaticBitmap* m_bitmap2;
	wxBitmapButton* m_bpButton3;
	wxStaticBitmap* m_bitmap4;
	wxBitmapButton* m_bpButton31;

	// Virtual event handlers, override them in your derived class
	virtual void PlayClick(wxCommandEvent& event);
	virtual void ManualClick(wxCommandEvent& event);


public:

	SignDominAI(wxWindow* parent, wxWindowID id = wxID_ANY, const wxString& title = _("SignDomin-AI"), const wxPoint& pos = wxDefaultPosition, const wxSize& size = wxSize(1344, 756), long style = wxDEFAULT_FRAME_STYLE | wxTAB_TRAVERSAL);

	~SignDominAI();

};

