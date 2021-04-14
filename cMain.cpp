#include <string>
#include <wx/splitter.h>
#include <wx/textfile.h>
#include "cMain.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "LineSearch.h"
#include "StationNames.h"
#include "CreateLines.h"
#include <list>

wxBEGIN_EVENT_TABLE(cMain, wxFrame)

wxEND_EVENT_TABLE()

cMain::cMain() : wxFrame(nullptr, wxID_ANY, "Jumping Someone Else's Train", wxPoint(30, 30), wxDefaultSize)
{
	// Seed random number generator
	srand((unsigned int)time(NULL));

	lines = CreateLines();



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

	wxBoxSizer* leftSideSizer = new wxBoxSizer(wxVERTICAL);

	// Options for number of adults or children
	wxArrayString ticketsComboChoices;
	ticketsComboChoices.Add("0");
	ticketsComboChoices.Add("1");
	ticketsComboChoices.Add("2");
	ticketsComboChoices.Add("3");
	ticketsComboChoices.Add("4");
	ticketsComboChoices.Add("5");

	// Create both comboboxes for entering number of adults or children
	m_adultcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);
	m_childcombo = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);

	// Create text placed next to comboboxes that informs what info should be entered in each box
	m_adulttext = new wxStaticText(leftpanel, wxID_ANY, "Number of Adults:");
	m_childtext = new wxStaticText(leftpanel, wxID_ANY, "Number of Children:");



	wxBoxSizer* adultSizer = new wxBoxSizer(wxHORIZONTAL);
	adultSizer->Add(m_adulttext, 0, wxALL, 2);
	adultSizer->Add(m_adultcombo, 0, wxALL, 2);
	
	leftSideSizer->Add(adultSizer, 0, wxALL, 5);

	wxBoxSizer* childSizer = new wxBoxSizer(wxHORIZONTAL);
	childSizer->Add(m_childtext, 0, wxALL, 2);
	childSizer->Add(m_childcombo, 0, wxALL, 2);

	leftSideSizer->Add(childSizer, 0, wxALL, 5);


	wxStaticText* dummy1 = new wxStaticText(leftpanel, wxID_ANY, "");
	wxBoxSizer* DummySizer1 = new wxBoxSizer(wxHORIZONTAL);
	DummySizer1->Add(dummy1, 0);
	leftSideSizer->Add(DummySizer1, 0, wxTOP, 5);


	/*Calls vector "stationnames from 
	StationNames.h header file and iterates 
	through the vector adding the strings
	to the ComboBox in the GUI
	*/
	wxArrayString stationsComboChoices;
	for (size_t i = 0; i < stationnames.size(); ++i)
	{
		stationsComboChoices.Add(stationnames[i]);
	}




	// Create comboboxes for station selection

	m_fromstation = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);
	m_tostation = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxDefaultPosition, wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);


	// Text for Station selection
	m_fromtext = new wxStaticText(leftpanel, wxID_ANY, "From:");
	m_totext = new wxStaticText(leftpanel, wxID_ANY, "To:");

	wxBoxSizer* FromSizer = new wxBoxSizer(wxHORIZONTAL);
	FromSizer->Add(m_fromtext, 0, wxALL, 2);
	FromSizer->Add(m_fromstation, 0, wxALL, 2);

	leftSideSizer->Add(FromSizer, 0, wxALL, 5);

	wxBoxSizer* ToSizer = new wxBoxSizer(wxHORIZONTAL);
	ToSizer->Add(m_totext, 0, wxALL, 2);
	ToSizer->Add(m_tostation, 0, wxALL, 2);

	leftSideSizer->Add(ToSizer, 0, wxALL, 2);

	wxStaticText* dummy2 = new wxStaticText(leftpanel, wxID_ANY, "");
	wxBoxSizer* DummySizer2 = new wxBoxSizer(wxHORIZONTAL);
	DummySizer2->Add(dummy2, 0);
	leftSideSizer->Add(DummySizer2, 0, wxTOP, 5);



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
	m_dayinput = new wxComboBox(leftpanel, 200, wxEmptyString, wxDefaultPosition, wxDefaultSize, dayComboChoices, wxCB_DROPDOWN);
	m_monthinput = new wxComboBox(leftpanel, 201, wxEmptyString, wxDefaultPosition, wxDefaultSize, monthComboChoices, wxCB_DROPDOWN);
	m_yearinput = new wxComboBox(leftpanel, 202, wxEmptyString, wxDefaultPosition, wxDefaultSize, yearComboChoices, wxCB_DROPDOWN);

	
	// Text for date input
	m_whendaytext = new wxStaticText(leftpanel, wxID_ANY, "When: Day:");
	m_monthtext = new wxStaticText(leftpanel, wxID_ANY, "Month:");
	m_yeartext = new wxStaticText(leftpanel, wxID_ANY, "Year:");


	wxBoxSizer* DateSizer = new wxBoxSizer(wxHORIZONTAL);
	DateSizer->Add(m_whendaytext, 0, wxALL, 2);
	DateSizer->Add(m_dayinput, 0, wxRIGHT, 20);
	DateSizer->Add(m_monthtext, 0, wxRIGHT, 2);
	DateSizer->Add(m_monthinput, 0, wxRIGHT, 20);
	DateSizer->Add(m_yeartext, 0, wxRIGHT, 2);
	DateSizer->Add(m_yearinput, 0);

	leftSideSizer->Add(DateSizer, 0, wxALL, 5);


	m_timebutton = new wxButton(leftpanel, wxID_ANY, "Get Times");
	m_timebutton->Bind(wxEVT_BUTTON, &cMain::OnTimeButtonClick, this);
	
	m_timeprev = new wxButton(leftpanel, wxID_ANY, "Previous Train");
	m_timeprev->Enable(false);
	m_timeprev->Bind(wxEVT_BUTTON, &cMain::OnTimePrevButtonClick, this);

	m_timenext = new wxButton(leftpanel, wxID_ANY, "Next Train");
	m_timenext->Enable(false);
	m_timenext->Bind(wxEVT_BUTTON, &cMain::OnTimeNextButtonClick, this);


	wxBoxSizer* TimeButtonsSizer = new wxBoxSizer(wxHORIZONTAL);

	TimeButtonsSizer->Add(m_timebutton, 0, wxLEFT, 2);
	TimeButtonsSizer->Add(m_timeprev, 1, wxLEFT, 20);
	TimeButtonsSizer->Add(m_timenext, 1);

	leftSideSizer->Add(TimeButtonsSizer, 0, wxALL, 10);

	m_journeytext1 = new wxStaticText(leftpanel, wxID_ANY, wxEmptyString);

	leftSideSizer->Add(m_journeytext1, 0,  wxALL, 7);

	// Listbox to display available times based on 
	m_timelist = new wxListBox(leftpanel,  wxID_ANY, wxDefaultPosition, wxSize(50, 160) );
	m_timelist->Bind(wxEVT_LISTBOX, &cMain::OnTrainTimeClick, this);

	// Text for available times
	m_timetext = new wxStaticText(leftpanel, wxID_ANY, "Available times:");

	wxBoxSizer* TimeListSizer = new wxBoxSizer(wxHORIZONTAL);

	TimeListSizer->Add(m_timetext, 1, wxLEFT, 2);
	TimeListSizer->Add(m_timelist, 1, wxLEFT, 2);

	leftSideSizer->Add(TimeListSizer, 1, wxALL, 5);

	std::string explain = "On the train diagram, red seats represent seats that have\nalready been booked, while orange seats represent seats that\nare unavailable for booking due to COVID restrictions";
							
	m_explaintext = new wxStaticText(leftpanel, wxID_ANY, explain);

	leftSideSizer->Add(m_explaintext, 1, wxALL, 7);

	Train temp;
	height = temp.getHeight();
	width = temp.getWidth();


	m_journeytext2 = new wxStaticText(rightpanel, wxID_ANY, "HELLO!");

	// Initiate button array and grid sizer to place buttons in
	trainbtn1 = new wxToggleButton*[width * height];
	wxGridSizer* traingrid1 = new wxGridSizer(height, width, 0, 0);

	

	
	// Loop through the height and width
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			// Create new button placed into the array of buttons
			trainbtn1[j * height + i] = new wxToggleButton(rightpanel, 10000 + (j * height + i), wxEmptyString);
			// Add new button into the grid sizer
			traingrid1->Add(trainbtn1[j * height + i], 1, wxEXPAND);
			// Execute OnTrainButtonClick when the button is clicked
			trainbtn1[j * height + i]->Bind(wxEVT_TOGGLEBUTTON, &cMain::OnTrainButtonClick, this);
			trainbtn1[j * height + i]->Enable(false);
		}
	}

	// Repeat same process as previously with right side of train display
	trainbtn2 = new wxToggleButton * [width * height];
	wxGridSizer* traingrid2 = new wxGridSizer(height, width, 0, 0);

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			trainbtn2[j * height + i] = new wxToggleButton(rightpanel, 10000 + (width * height) + (j * height + i), wxEmptyString);
			traingrid2->Add(trainbtn2[j * height + i], 1, wxEXPAND);
			trainbtn2[j * height + i]->Bind(wxEVT_TOGGLEBUTTON, &cMain::OnTrainButtonClick, this);
			trainbtn2[j * height + i]->Enable(false);
		}
	}

	// Add both side sizers into a new sizer 
	wxBoxSizer* traingridboth = new wxBoxSizer(wxHORIZONTAL);
	traingridboth->Add(traingrid1, 1, wxEXPAND | wxRIGHT, 20);
	traingridboth->Add(traingrid2, 1, wxEXPAND | wxLEFT, 20);

	rightSideSizer = new wxBoxSizer(wxVERTICAL);

	m_submit = new wxButton(rightpanel, 101, "Submit");
	m_submit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnSubmitButtonClick, this);
	m_submit->Enable(false);

	rightSideSizer->Add(m_journeytext2, 0, wxALIGN_CENTER | wxTOP, 5);
	rightSideSizer->Add(traingridboth, 4, wxEXPAND | wxALL, 2);
	rightSideSizer->Add(m_submit, 1, wxEXPAND | wxALL, 20);

	// Assign this new sizer to the right side of the page
	rightpanel->SetSizer(rightSideSizer);
	rightSideSizer->Layout();

	leftpanel->SetSizer(leftSideSizer);
	leftSideSizer->Layout();

	// Split the frame into the two panels
	splittermain->SplitVertically(leftpanel, rightpanel);

	// Set split panel sizer to the main sizer of the frame
	this->SetSizer(sizermain);
	sizermain->SetSizeHints(this);

	m_messagedialog = new wxMessageDialog(this, "hello", "Hi", wxOK);
}

cMain::~cMain()
{
	delete[] trainbtn1;
	delete[] trainbtn2;
}


void cMain::updateTrainButtons(Train t)
{
	// Updates train buttons to display correct info based on train object
	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (t.checkSeat(i, j) == 0)
			{
				// If booked...
				trainbtn1[j * height + i]->Enable(false);									// Disable button
				trainbtn1[j * height + i]->SetBackgroundColour(wxColour(247, 55, 52, 120)); // Set background and foreground to red
				trainbtn1[j * height + i]->SetForegroundColour(wxColour(247, 55, 52, 120));
			}
			else if (t.checkSeat(i, j) == 1)
			{
				// If unavailable for social distancing...
				trainbtn1[j * height + i]->Enable(false);									// Disable button
				trainbtn1[j * height + i]->SetBackgroundColour(wxColour(255, 165, 0, 120));	// Set background and foreground to orange
				trainbtn1[j * height + i]->SetForegroundColour(wxColour(255, 165, 0, 120));
			}
			else if (t.checkSeat(i, j) == 2)
			{
				// If available, check if max buttons are already pressed
				if (clicked[pos] == noPeople)
				{
					trainbtn1[j * height + i]->Enable(false);
				}
				else
				{
					trainbtn1[j * height + i]->Enable(true);
				}					
				// Remove colouring
				trainbtn1[j * height + i]->SetBackgroundColour(wxNullColour);	// Reset background and forground to default
				trainbtn1[j * height + i]->SetForegroundColour(wxNullColour);
			}

			// Same method but for the 2nd train button array
			if (t.checkSeat(i, j + width) == 0)
			{
				trainbtn2[j * height + i]->Enable(false);
				trainbtn2[j * height + i]->SetBackgroundColour(wxColour(247, 55, 52, 120));
				trainbtn2[j * height + i]->SetForegroundColour(wxColour(247, 55, 52, 120));
			}
			else if (t.checkSeat(i, j + width) == 1)
			{
				trainbtn2[j * height + i]->Enable(false);
				trainbtn2[j * height + i]->SetBackgroundColour(wxColour(255, 165, 0, 120));
				trainbtn2[j * height + i]->SetForegroundColour(wxColour(255, 165, 0, 120));
			}
			else if (t.checkSeat(i, j + width) == 2)
			{
				if (clicked[pos] == noPeople)
				{
					trainbtn2[j * height + i]->Enable(false);
				}
				else 
				{
					trainbtn2[j * height + i]->Enable(true);
				}

				trainbtn2[j * height + i]->SetBackgroundColour(wxNullColour);
				trainbtn2[j * height + i]->SetForegroundColour(wxNullColour);
			}
			trainbtn1[j * height + i]->SetValue(false);
			trainbtn2[j * height + i]->SetValue(false);
		}
	}

	int x, y;

	if (!selected.empty())
	{
		for (int n : selected[pos])
		{
			x = n / height;
			y = n % height;
			if (n < width*height)
			{
				trainbtn1[x * height + y]->SetValue(true);
				trainbtn1[x * height + y]->Enable(true);
			}
			else 
			{
				trainbtn2[x * height + y - (height * width)]->SetValue(true);
				trainbtn2[x * height + y - (height * width)]->Enable(true);
			}
		}
	}

	if (clicked[pos] == noPeople)
	{

	}
}

void cMain::OnSubmitButtonClick(wxCommandEvent& evt)
{
	// Get info from combo boxes
	std::string noOfChildren = (m_childcombo->GetValue()).ToStdString();
	std::string noOfAdults = (m_adultcombo->GetValue()).ToStdString();
	
	std::string traveldate = (m_dayinput->GetValue()).ToStdString() + "/" + (m_monthinput->GetValue()).ToStdString() + "/" + (m_yearinput->GetValue()).ToStdString();
	std::string traveltime = (m_timelist->GetString(m_timelist->GetSelection())).ToStdString();

	std::string depStation = (m_fromstation->GetValue()).ToStdString();
	std::string arrStation = (m_tostation->GetValue()).ToStdString();

	// Find changover stations from route vector and add to string
	std::string changeover = "";
	for (std::vector<std::string>::iterator t = route.begin(); t != route.end(); ++t)
	{
		if (t != route.begin() && t != route.end() - 1)
		{
			changeover += *t + ", ";
		}
	}

	// If changeover is empty...
	if (changeover == "")
	{
		// Set to display no changovers
		changeover = "No changeover required";
	}
	else
	{
		// Otherwise remove final comma from string
		changeover = changeover.substr(0, changeover.size() - 2);
	}


	std::string BookingConfirm = std::string("Booking Confirmation\nDeparting from: ") + depStation + std::string("\nArriving at: ") + 
								arrStation + std::string("\nDeparting at: ") + traveldate + std::string(" ") + traveltime + std::string("\nAdults: ") + 
								noOfAdults + std::string("\nChildren: ") + noOfChildren + std::string("\nChangover: ") + changeover;

	m_messagedialog->SetMessage(BookingConfirm);
	m_messagedialog->ShowModal();
	evt.Skip();
}


void cMain::OnTimeButtonClick(wxCommandEvent& evt)
{
	// Clear listbox
	m_timelist->Clear();

	journeys.clear();

	// Find number of people being booked for
	noPeople = (m_adultcombo->GetCurrentSelection()) + (m_childcombo->GetCurrentSelection());

	// Validate adult and child input
	if (m_adultcombo->GetValue() == wxEmptyString || m_childcombo->GetValue() == wxEmptyString)
	{
		m_messagedialog->SetMessage("Error: No value for adult and child tickets selected");
		m_messagedialog->ShowModal();
		return;
	}

	// Get departure and arrival stations from GUI
	wxString depStation = m_fromstation->GetValue();
	wxString arrStation = m_tostation->GetValue();

	// Validate station input
	if (depStation == wxEmptyString || arrStation == wxEmptyString)
	{
		m_messagedialog->SetMessage("Error: Arrival or departure station not selected");
		m_messagedialog->ShowModal();
		return;
	}

	if (m_dayinput->GetValue() == wxEmptyString || m_monthinput->GetValue() == wxEmptyString || m_yearinput->GetValue() == wxEmptyString)
	{
		m_messagedialog->SetMessage("Error: Date input not selected");
		m_messagedialog->ShowModal();
		return;
	}

	wxArrayString timesFormat;
	std::vector<int> times;
	int noOfTimes = 10;
	
	// Creates random times for train departures
	for (int i = 0; i < noOfTimes; i++)
	{
		times.push_back(rand() % 900 + 420);
		std::string s = "";
		if (times[i] / 60 < 10)
		{
			s += "0";
		}
		s += std::to_string(times[i] / 60);
		s += ":";
		if (times[i] % 60 < 10)
		{
			s += "0";
		}
		s += std::to_string(times[i] % 60);
		timesFormat.Add(s);
	}

	// Sorts with earliest time first
	std::sort(times.begin(), times.end());
	std::sort(timesFormat.begin(), timesFormat.end());

	// Adds arraystring to listbox
	m_timelist->InsertItems(timesFormat, 0);

	// Creates vector of journeys, representing each time option
	for (int i = 0; i < noOfTimes; i++)
	{
		journeys.push_back(Journey(lines, depStation.ToStdString(), arrStation.ToStdString(), times[i]));
	}

	route = journeys[0].getRoute();
	
	// Reset selected and clicked for new journey
	selected.clear();
	clicked.clear();
	selected.resize(route.size() - 1);
	clicked.resize(route.size() - 1);

	// Disable next and prev buttons until a new time is selected
	m_timenext->Enable(false);
	m_timeprev->Enable(false);

	// Set initial values for pos and text boxes
	pos = 0;
	m_journeytext1->SetLabel(route[0] + "-" + route[1]);
	m_journeytext2->SetLabel(route[0] + "-" + route[1]);
	

	// Reset sizer to center text
	rightSideSizer->Layout();
	evt.Skip();
}

void cMain::OnTimeNextButtonClick(wxCommandEvent& evt)
{
	// Check not in the last position
	if (pos < route.size()-2)
	{
		// Increase position
		pos++;
		// Set labels to appropriate stage of journey
		m_journeytext1->SetLabel(route[pos] + "-" + route[pos + 1]);
		m_journeytext2->SetLabel(route[pos] + "-" + route[pos + 1]);


		updateTrainButtons(journeys[m_timelist->GetSelection()].getTrain(pos));
	}
	// Reset sizer to center text
	rightSideSizer->Layout();
	evt.Skip();
}

void cMain::OnTimePrevButtonClick(wxCommandEvent& evt)
{
	// Check not in first position
	if (pos > 0)
	{
		// Same as next button
		pos--;
		m_journeytext1->SetLabel(route[pos] + "-" + route[pos + 1]);
		m_journeytext2->SetLabel(route[pos] + "-" + route[pos + 1]);

		updateTrainButtons(journeys[m_timelist->GetSelection()].getTrain(pos));
	}
	rightSideSizer->Layout();
	evt.Skip();
}

void cMain::OnTrainTimeClick(wxCommandEvent& evt)
{
	selected.clear();
	clicked.clear();
	selected.resize(route.size() - 1);
	clicked.resize(route.size() - 1);

	// Enable next and previous button if more than 1 journey present and a time selection has been made
	if (route.size() > 2 && m_timelist->GetSelection() != wxNOT_FOUND)
	{
		m_timenext->Enable(true);
		m_timeprev->Enable(true);
	}
	else
	{
		m_timenext->Enable(false);
		m_timeprev->Enable(false);
	}
	updateTrainButtons(journeys[m_timelist->GetSelection()].getTrain(0));


}

void cMain::OnTrainButtonClick(wxCommandEvent& evt)
{
	/* The grid of buttons is layed out in this form, with the first item in the top left corner
	*  and the numbers ascending down the columns
	*
	*	0	4	8	12
	*	1	5	9	13
	*	2	6	10	14
	*	3	7	11	15
	*/

	// Finds x and y position of clicked button
	int x = (evt.GetId() - 10000) / height;
	int y = (evt.GetId() - 10000) % height;

	int value = x * height + y;

	// Check if button is already in vector
	std::vector<int>::iterator it = std::find(selected[pos].begin(), selected[pos].end(), value);

	if (it != selected[pos].end())
	{
		// Element found
		selected[pos].erase(it);
		clicked[pos]--;
	}
	else
	{
		// Element not found
		selected[pos].push_back(value);
		clicked[pos]++;
	}

	if (clicked[pos] == noPeople)
	{
		// Disable all buttons
		for (int i = 0; i < height*width; i++)
		{
			trainbtn1[i]->Enable(false);
			trainbtn2[i]->Enable(false);
		}
		// Reenable buttons that are currently selected
		for (int i = 0; i < selected[pos].size(); i++)
		{
			// Checks which of the button array this specific seat is part of
			if (selected[pos][i] < height * width)
			{
				trainbtn1[selected[pos][i]]->Enable(true);
			}
			else
			{
				trainbtn2[selected[pos][i]-height*width]->Enable(true);
			}
		}
	}
	else
	{
		/* Will enable buttons when the seats selected is less than noPeople
		*  This allows for the user to unselect a seat when they're at the max,
		*  the other seats will enable again allowing them to make a new selection
		*/
		for (int i = 0; i < height; i++)
		{
			for (int j = 0; j < width*2; j++)
			{
				if (j < width && journeys[m_timelist->GetSelection()].getTrain(pos).checkSeat(i, j) == 2)
				{
					trainbtn1[j*height+i]->Enable(true);
				}
				else if (journeys[m_timelist->GetSelection()].getTrain(pos).checkSeat(i, j) == 2)
				{
					trainbtn2[j*height+i-(width*height)]->Enable(true);
				}
			}
		}
	}
	
	int fullSelection = 0;

	for (int n : clicked)
	{
		if (n == noPeople)
		{
			fullSelection++;
		}
	}

	if (fullSelection == clicked.size())
	{
		m_submit->Enable(true);
	}
	else
	{
		m_submit->Enable(false);
	}

	evt.Skip();
}