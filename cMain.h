/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- cMain.h				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 12/04/21													*
*	Update Description:	Removed ticket type radio buttons and tempory		*
*	TextCtrl																*
*																			*
*****************************************************************************/

#ifndef MAIN_HEADER
#define MAIN_HEADER

#include "wx/wx.h"
#include <wx/tglbtn.h>
#include <wx/splitter.h>
#include <wx/textfile.h>
#include "Train.h"
#include "Journey.h"

#include <vector>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	void OnTrainButtonClick(wxCommandEvent& evt);
	void OnSubmitButtonClick(wxCommandEvent& evt);
	void OnTimeButtonClick(wxCommandEvent& evt);
	void OnTimeNextButtonClick(wxCommandEvent& evt);
	void OnTimePrevButtonClick(wxCommandEvent& evt);
	void OnTrainTimeClick(wxCommandEvent& evt);
	void updateTrainButtons(Train t);

	int width;
	int height;

	int** trainArr;	

	std::vector<int> clicked;
	std::vector<std::vector<int>> selected;
	std::vector<Journey> journeys;

	wxString day;
	wxString month;
	wxString year;



	std::vector<std::vector<std::string>> lines;

	std::vector<std::string> route;

	int pos;
	int noPeople;

public:
	

	wxPanel* rightpanel = nullptr;
	wxPanel* leftpanel = nullptr;

	wxComboBox* m_adultcombo = nullptr;
	wxComboBox* m_childcombo = nullptr;
	wxStaticText* m_adulttext = nullptr;
	wxStaticText* m_childtext = nullptr;


	wxComboBox* m_fromstation = nullptr;
	wxComboBox* m_tostation = nullptr;
	wxStaticText* m_fromtext = nullptr;
	wxStaticText* m_totext = nullptr;

	wxStaticText* m_whendaytext = nullptr;
	wxStaticText* m_monthtext = nullptr;
	wxStaticText* m_yeartext = nullptr;
	wxComboBox* m_dayinput = nullptr;
	wxComboBox* m_monthinput = nullptr;
	wxComboBox* m_yearinput = nullptr;

	wxButton* m_timebutton = nullptr;
	wxButton* m_timenext = nullptr;
	wxButton* m_timeprev = nullptr;

	wxStaticText* m_journeytext1 = nullptr;
	wxListBox* m_timelist = nullptr;
	wxStaticText* m_timetext = nullptr;
	
	wxStaticText* m_explaintext = nullptr;

	wxToggleButton** trainbtn1 = nullptr;
	wxToggleButton** trainbtn2 = nullptr;

	wxStaticText* m_journeytext2 = nullptr;

	wxButton* m_submit = nullptr;

	wxBoxSizer* rightSideSizer;

	wxMessageDialog* m_messagedialog = nullptr;

	wxDECLARE_EVENT_TABLE();
};

#endif
