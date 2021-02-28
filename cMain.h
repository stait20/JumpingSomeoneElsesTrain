#pragma once
#include "wx/wx.h"

class cMain : public wxFrame
{
public:
	cMain();
	~cMain();

private:
	void OnRadioBoxChange(wxCommandEvent& evt);

public:
	wxRadioBox* m_rad1 = nullptr;
	wxTextCtrl* m_textctrl1 = nullptr;

	wxComboBox* m_adultcombo = nullptr;
	wxComboBox* m_childcombo = nullptr;
	wxStaticText* m_adulttext = nullptr;
	wxStaticText* m_childtext = nullptr;


	wxDECLARE_EVENT_TABLE();
};

