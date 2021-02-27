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

	wxDECLARE_EVENT_TABLE();
};

