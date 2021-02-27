#define _CRT_SECURE_NO_WARNINGS
#include <string>

#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_RADIOBOX(101, OnRadioBoxChange)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Jumping Someone Else's Train", wxPoint(30, 30), wxSize(800, 600))
{
	
	wxPanel* panel = new wxPanel(this, wxID_ANY);

	// Options to be used for text box put into a wxArrayString
	wxArrayString choices;
	choices.Add("Adult");
	choices.Add("Child");

	// Create radio buttons
	m_rad1 = new wxRadioBox(panel, 101, "Select one of the options", wxPoint(10, 10), wxDefaultSize, choices, 2, wxRA_VERTICAL);

	// Temp text box to show selection
	m_textctrl1 = new wxTextCtrl(panel, wxID_ANY, m_rad1->GetString(m_rad1->GetSelection()), wxPoint(10, 100), wxSize(140, wxDefaultCoord));
}

cMain::~cMain()
{
}

// Temp function to display what radio button is selected
void cMain::OnRadioBoxChange(wxCommandEvent& evt)
{
	wxString text = m_rad1->GetString(evt.GetSelection());
	m_textctrl1->SetValue(text);
}

