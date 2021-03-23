#ifndef MAIN_HEADER
#define MAIN_HEADER

#include "wx/wx.h"
#include <wx/tglbtn.h>

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	void OnRadioBoxChange(wxCommandEvent& evt);
	void OnTrainButtonClick(wxCommandEvent& evt);
	void OnSubmitButtonClick(wxCommandEvent& evt);

	int height = 8;
	int width = 2;

	int** trainArr;

public:
	
	wxPanel* rightpanel = nullptr;
	wxPanel* leftpanel = nullptr;

	wxRadioBox* m_rad1 = nullptr;
	wxTextCtrl* m_textctrl1 = nullptr;

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

	wxListBox* m_timelist = nullptr;
	wxStaticText* m_timetext = nullptr;

	wxToggleButton** trainbtn1 = nullptr;
	wxToggleButton** trainbtn2 = nullptr;

	wxButton* m_submit = nullptr;

	wxDECLARE_EVENT_TABLE();
};

#endif
