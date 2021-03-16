#include <string>
#include <wx/splitter.h>
#include "cMain.h"

wxBEGIN_EVENT_TABLE(cMain, wxFrame)
	EVT_RADIOBOX(100, OnRadioBoxChange)
wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Jumping Someone Else's Train", wxPoint(30, 30), wxDefaultSize)
{
	/*  Split screen vertically into two equal sections. 
	*   Things can be added to either rightpanel or leftpanel
	*   depending on where they should be placed
	*/
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
	m_rad1 = new wxRadioBox(leftpanel, 100, "Select one of the options", wxPoint(10, 10), wxDefaultSize, radioChoices, 2, wxRA_VERTICAL);

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


	// Initiate button array and grid sizer to place buttons in
	trainbtn1 = new wxButton*[width * height];
	wxGridSizer* traingrid1 = new wxGridSizer(height, width, 0, 0);

	// Loop through the height and width
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Create new button placed into the array of buttons
			trainbtn1[j * height + i] = new wxButton(rightpanel, 10000 + (j * height + i));
			// Add new button into the grid sizer
			traingrid1->Add(trainbtn1[j * height + i], 1, wxEXPAND);
			// Execute OnTrainButtonClick when the button is clicked
			trainbtn1[j * height + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTrainButtonClick, this  );
		}
	}

	// Repeat same process as previously with right side of train display
	trainbtn2 = new wxButton * [width * height];
	wxGridSizer* traingrid2 = new wxGridSizer(height, width, 0, 0);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			trainbtn2[j * height + i] = new wxButton(rightpanel, 10000 + (width * height) + (j * height + i));
			traingrid2->Add(trainbtn2[j * height + i], 1, wxEXPAND);
			trainbtn2[j * height + i]->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnTrainButtonClick, this);
		}
	}

	// Add both side sizers into a new sizer 
	wxBoxSizer* traingridboth = new wxBoxSizer(wxHORIZONTAL);
	traingridboth->Add(traingrid1, 1, wxEXPAND | wxRIGHT, 20);
	traingridboth->Add(traingrid2, 1, wxEXPAND | wxLEFT, 20);

	wxBoxSizer* rightSideSizer = new wxBoxSizer(wxVERTICAL);

	m_submit = new wxButton(rightpanel, 101, "Submit");

	rightSideSizer->Add(traingridboth, 4, wxEXPAND | wxALL, 5);
	rightSideSizer->Add(m_submit, 1, wxEXPAND | wxALL, 20);

	// Assign this new sizer to the right side of the page
	rightpanel->SetSizer(rightSideSizer);
	rightSideSizer->Layout();







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

void cMain::OnTrainButtonClick(wxCommandEvent& evt)
{
	

	/* The grid of buttons is layed out in this form, with the first item in the top left corner
	*  and the numbers ascending down the columns		
	* 
	*	0	4	8
	*	1	5	9
	*	2	6	10
	*	3	7	11
	*/

	// Finds x and y position of clicked button
	int x = (evt.GetId() - 10000) / height;
	int y = (evt.GetId() - 10000) % height;


	std::string pos = std::to_string(x * height + y);
	m_textctrl1->SetValue(pos);

	if (trainbtn1[x * height + y]->Enable(true))
	{
		trainbtn1[x * height + y]->Enable(false);
	}
	/*else
	{
		trainbtn1[x * height + y]->Enable(false);
	}*/
}