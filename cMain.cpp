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
	choices.Add("Single");
	choices.Add("Return");

	// Create radio buttons
	m_rad1 = new wxRadioBox(panel, 101, "Select one of the options", wxPoint(10, 10), wxDefaultSize, choices, 2, wxRA_VERTICAL);

	// Temp text box to show selection
	m_textctrl1 = new wxTextCtrl(panel, wxID_ANY, m_rad1->GetString(m_rad1->GetSelection()), wxPoint(10, 100), wxSize(140, wxDefaultCoord));

	// Options for number of adults or children
	wxArrayString comboChoices;
	comboChoices.Add("0");
	comboChoices.Add("1");
	comboChoices.Add("2");
	comboChoices.Add("3");
	comboChoices.Add("4");
	comboChoices.Add("5");

	// Create both comboboxes for entering number of adults or children
	m_adultcombo = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxPoint(130, 140), wxDefaultSize, comboChoices, wxCB_DROPDOWN);
	m_childcombo = new wxComboBox(panel, wxID_ANY, wxEmptyString, wxPoint(130, 170), wxDefaultSize, comboChoices, wxCB_DROPDOWN);

	// Create text placed next to comboboxes that informs what info should be entered in each box
	m_adulttext = new wxStaticText(panel, wxID_ANY, "Number of Adults:", wxPoint(10, 145), wxDefaultSize);
	m_childtext = new wxStaticText(panel, wxID_ANY, "Number of Children:", wxPoint(10, 175), wxDefaultSize);

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

