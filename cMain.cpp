﻿#include <string>
#include <wx/splitter.h>
#include <wx/textfile.h>
#include "cMain.h"
#include <iostream>
#include <fstream>
#include <vector>
#include "LineSearch.h"
#include "StationNames.h"
#include "Lines.h"
#include <list>

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
	m_adultcombo = new wxComboBox(leftpanel, wxID_ANY, "0", wxPoint(130, 140), wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);
	m_childcombo = new wxComboBox(leftpanel, wxID_ANY, "0", wxPoint(130, 170), wxDefaultSize, ticketsComboChoices, wxCB_DROPDOWN);

	//m_adultcombo->Bind

	// Create text placed next to comboboxes that informs what info should be entered in each box
	m_adulttext = new wxStaticText(leftpanel, wxID_ANY, "Number of Adults:", wxPoint(10, 145), wxDefaultSize);
	m_childtext = new wxStaticText(leftpanel, wxID_ANY, "Number of Children:", wxPoint(10, 175), wxDefaultSize);


	/* Array for storing station names
	* Eventually will read stations from
	* external file and add them to list
	*/

	//wxArrayString stationsComboChoices;
	//wxString root = wxGetCwd();
	//wxString station = root + wxT("stationnames.txt");
	//wxTextFile file;
	//file.Open(station);
	//int i;
	//for (i = 0; i < file.GetCount(i); i++)
	//{
	//	wxString name1 = file.Getline(i);
	//	stationsComboChoices.Insert(name1, i);
	//}

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

	//std::ifstream file;
	//file.open("aberdeentoedinburgh.txt");
	//std::vector < std::string> stationnames;
	//std::string input = "Edi";
	//if (!file)
	//{
	//	input = "no stations here";
	//	stationsComboChoices.Add(input);
	//}
	//while (!file.eof())
	//{
	//	getline(file, input);
	//	stationsComboChoices.Add(input);
	//}
	//file.close();
	//while (file >> input)
	//{
	//	stationnames.push_back(input);
	//	//stationsComboChoices.Add(input);
	//}

	//stationsComboChoices.Add(input);
	
	//for (std::string>::iterator it = stationnames.begin(); it != stationnames.end(); ++it)
	//{
	//	stationsComboChoices.Add(stationnames);
	//}

	//for (std::vector<std::string>::iterator it = stationnames.begin(); it != stationnames.end(); ++it)
	//{
	//	wxString test45 = it->c_str();
	//	stationsComboChoices.Insert(it->c_str(), it);
	//}

	//for (std::string stationnames : stationnames)
	//{
	//	std::cout << stationnames << "\n";
	//}
	
	//std::string station = "Glasgow Central";

	//wxArrayString stationsComboChoices;
	//stationsComboChoices.Add(stationnames);
	//stationsComboChoices.Add("stationnames.txt");
	//stationsComboChoices.Add("Pollockshaws West");
	//stationsComboChoices.Add(station);
	

	// Create comboboxes for station selection

	m_fromstation = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(50, 220), wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);
	m_tostation = new wxComboBox(leftpanel, wxID_ANY, wxEmptyString, wxPoint(50, 250), wxDefaultSize, stationsComboChoices, wxCB_DROPDOWN);


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



	

	height = t.getHeight();
	width = t.getWidth();


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
			// Check state of seat...
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
			if (t.checkSeat(i, j+width) == 0)
			{
				trainbtn2[j * height + i]->Enable(false);
				trainbtn2[j * height + i]->SetBackgroundColour(wxColour(247, 55, 52, 120));
				trainbtn2[j * height + i]->SetForegroundColour(wxColour(247, 55, 52, 120));
			}
			else if (t.checkSeat(i, j+width) == 1)
			{
				trainbtn2[j * height + i]->Enable(false);
				trainbtn2[j * height + i]->SetBackgroundColour(wxColour(255, 165, 0, 120));
				trainbtn2[j * height + i]->SetForegroundColour(wxColour(255, 165, 0, 120));
			}
		}
	}

	// Add both side sizers into a new sizer 
	wxBoxSizer* traingridboth = new wxBoxSizer(wxHORIZONTAL);
	traingridboth->Add(traingrid1, 1, wxEXPAND | wxRIGHT, 20);
	traingridboth->Add(traingrid2, 1, wxEXPAND | wxLEFT, 20);

	wxBoxSizer* rightSideSizer = new wxBoxSizer(wxVERTICAL);

	m_submit = new wxButton(rightpanel, 101, "Submit");
	m_submit->Bind(wxEVT_COMMAND_BUTTON_CLICKED, &cMain::OnSubmitButtonClick, this);

	rightSideSizer->Add(traingridboth, 4, wxEXPAND | wxALL, 5);
	rightSideSizer->Add(m_submit, 1, wxEXPAND | wxALL, 20);

	// Assign this new sizer to the right side of the page
	rightpanel->SetSizer(rightSideSizer);
	rightSideSizer->Layout();

	// Split the frame into the two panels
	splittermain->SplitVertically(leftpanel, rightpanel);

	// Set split panel sizer to the main sizer of the frame
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
	/*wxString text = m_rad1->GetString(evt.GetSelection());
	m_textctrl1->SetValue(text);*/
}

void cMain::OnSubmitButtonClick(wxCommandEvent& evt)
{

}

void cMain::OnTrainButtonClick(wxCommandEvent& evt)
{
	// Find number of people being booked for
	int noPeople = (m_adultcombo->GetCurrentSelection()) + (m_childcombo->GetCurrentSelection());


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

	int value = x * height + y;

	// Check if button is already in vector
	std::vector<int>::iterator it = std::find(selected.begin(), selected.end(), value);

	if (it != selected.end())
	{
		// Element found
		selected.erase(it);
		clicked--;
	}
	else
	{
		// Element not found
		selected.push_back(value);
		clicked++;
	}

	

	std::string pos = std::to_string(noPeople);
	m_textctrl1->SetValue(pos);

	

	if (clicked == noPeople)
	{
		// Disable all buttons
		for (int i = 0; i < height*width; i++)
		{
			trainbtn1[i]->Enable(false);
			trainbtn2[i]->Enable(false);
		}
		// Reenable buttons that are currently selected
		for (int i = 0; i < selected.size(); i++)
		{
			// Checks which of the button array this specific seat is part of
			if (selected[i] < height * width)
			{
				trainbtn1[selected[i]]->Enable(true);
			}
			else
			{
				trainbtn2[selected[i]-height*width]->Enable(true);
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
				if (j < width && t.checkSeat(i, j) == 2)
				{
					trainbtn1[j*height+i]->Enable(true);
				}
				else if (t.checkSeat(i, j) == 2)
				{
					trainbtn2[j*height+i-(width*height)]->Enable(true);
				}
			}
		}
	}

}