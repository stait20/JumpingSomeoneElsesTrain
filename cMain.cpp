#include <string>
#include <wx/splitter.h>
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_RADIOBOX(101, OnRadioBoxChange)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Jumping Someone Else's Train", wxPoint(30, 30), wxDefaultSize)
{

	wxBoxSizer* sizermain = new wxBoxSizer(wxVERTICAL);
	wxSplitterWindow* splittermain = new wxSplitterWindow(this, wxID_ANY);
	splittermain->SetSashGravity(0.5);
	splittermain->SetMinimumPaneSize(20); 
	sizermain->Add(splittermain, 1, wxEXPAND, 0);


	leftpanel = new wxPanel(splittermain, wxID_ANY);
	rightpanel = new wxPanel(splittermain, wxID_ANY);

	// Options to be used for text box put into a wxArrayString
	wxArrayString radioChoices;
	radioChoices.Add("Single");
	radioChoices.Add("Return");

	// Create radio buttons
	m_rad1 = new wxRadioBox(leftpanel, 101, "Select one of the options", wxPoint(10, 10), wxDefaultSize, radioChoices, 2, wxRA_VERTICAL);

	// Temp text box to show selection
	m_textctrl1 = new wxTextCtrl(leftpanel, wxID_ANY, m_rad1->GetString(m_rad1->GetSelection()), wxPoint(10, 100), wxSize(140, wxDefaultCoord));

	// Options for number of adults or children
	wxArrayString ticketsComboChoices;
	ticketsComboChoices.Add("0");
	ticketsComboChoices.Add("1");
	ticketsComboChoices.Add("2");
	ticketsComboChoices.Add("3");
	ticketsComboChoices.Add("4");
	ticketsComboChoices.Add("5");

	// Create both comboboxes for entering number of adults or children
	m_adultcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(130, 140), wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);
	m_childcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(130, 170), wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);

	// Create text placed next to comboboxes that informs what info should be entered in each box
	m_adulttext = new wxStaticText(leftpanel, wxID_ANY, "Number of Adults:", wxPoint(10, 145), wxDefaultSize);
	m_childtext = new wxStaticText(leftpanel, wxID_ANY, "Number of Children:", wxPoint(10, 175), wxDefaultSize);


	/* Array for storing station names
	* Eventually will read stations from
	* external file and add them to list
	*/

	wxArrayString stationsComboChoices;
	stationsComboChoices.Add("Glasgow Central");
	stationsComboChoices.Add("Crossmyloof");
	stationsComboChoices.Add("Pollockshaws West");


	// Create comboboxes for station selection
	m_adultcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(50, 220), wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);
	m_childcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(50, 250), wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);


	// Text for Station selection
	m_fromtext = new wxStaticText(leftpanel, wxID_ANY, "From:", wxPoint(10, 225), wxDefaultSize);
	m_fromtext = new wxStaticText(leftpanel, wxID_ANY, "To:", wxPoint(10, 255), wxDefaultSize);


	/* Loops for creating arrays for day, month and year choices.
	*  The loops assign days as 1-31, months as 1-12 and years
	*  as 2021-2025. The year values may be changed later, as
	*  it is unlikely booking will go that far in the future  
	*/
	wxArrayString dayComboChoices;
	for (int i = 1; i <= 31; i++)
	{
		dayComboChoices.Add(std::to_string(i));
	}

	wxArrayString monthComboChoices;
	for (int i = 1; i <= 12; i++)
	{
		monthComboChoices.Add(std::to_string(i));
	}

	wxArrayString yearComboChoices;
	for (int i = 2021; i <= 2025; i++)
	{
		yearComboChoices.Add(std::to_string(i));
	}

	// Combo Boxes to input day, month and year
	m_dayinput = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(50, 280), wxDefaultSize, dayComboChoices, wxCB_DROPDOWN);
	m_monthinput = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(150, 280), wxDefaultSize, monthComboChoices, wxCB_DROPDOWN);
	m_yearinput = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(250, 280), wxDefaultSize, yearComboChoices, wxCB_DROPDOWN);


	// Text for date input
	m_whendaytext = new wxStaticText(leftpanel, wxID_ANY, "When: Day", wxPoint(10, 280), wxDefaultSize);
	m_monthtext = new wxStaticText(leftpanel, wxID_ANY, "Month", wxPoint(120, 280), wxDefaultSize);
	m_yeartext = new wxStaticText(leftpanel, wxID_ANY, "Year", wxPoint(200, 280), wxDefaultSize);


	// Listbox to display available times based on 
	m_timelist = new wxListBox(leftpanel, wxID_ANY, wxPoint(100, 320), wxSize(150, 200));

	// Text for available times
	m_timetext = new wxStaticText(leftpanel, wxID_ANY, "Available times:", wxPoint(10, 320), wxDefaultSize);

	int height = 8;
	int width = 2;


	trainbtn1 = new wxButton*[width * height];
	wxGridSizer* traingrid1 = new wxGridSizer(height, width, 0, 0);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			trainbtn1[j * width + i] = new wxButton(rightpanel, 10000 + (j * width + i));
			traingrid1->Add(trainbtn1[j * width + i], 1, wxEXPAND);
		}
	}


	trainbtn2 = new wxButton * [width * height];
	wxGridSizer* traingrid2 = new wxGridSizer(height, width, 0, 0);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			trainbtn2[j * width + i] = new wxButton(rightpanel, 10010 + (j * width + i));
			traingrid2->Add(trainbtn2[j * width + i], 1, wxEXPAND);
		}
	}

	wxBoxSizer* traingridboth = new wxBoxSizer(wxHORIZONTAL);
	traingridboth->Add(traingrid1, 1, wxEXPAND | wxRIGHT, 20);
	traingridboth->Add(traingrid2, 1, wxEXPAND | wxLEFT, 20);


	rightpanel->SetSizer(traingridboth);
	traingridboth->Layout();


	splittermain->SplitVertically(leftpanel, rightpanel);

	this->SetSizer(sizermain);
	sizermain->SetSizeHints(this);
}

cMain::~cMain()
{
	delete[] trainbtn1;
	delete[] trainbtn2;
}


// Temp function to display what radio button is selected
void cMain::OnRadioBoxChange(wxCommandEvent& evt)
{
	wxString text = m_rad1->GetString(evt.GetSelection());
	m_textctrl1->SetValue(text);
}

