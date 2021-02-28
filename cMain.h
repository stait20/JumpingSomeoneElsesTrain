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


	wxComboBox* m_fromstation = nullptr;
	wxComboBox* m_tostation = nullptr;
	wxStaticText* m_fromtext = nullptr;
	wxStaticText* m_totext = nullptr;

	wxDECLARE_EVENT_TABLE();
};

