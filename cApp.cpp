/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- cApp.cpp				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 23/02/21													*
*	Update Description:	Added basic wxWidgets framework to display GUI		*
*																			*
*****************************************************************************/

#include "cApp.h"

wxIMPLEMENT_APP(cApp);


cApp::cApp()
{
}

cApp::~cApp()
{
}

bool cApp::OnInit()
{
	m_frame1 = new cMain();
	m_frame1->Show();

	return true;
}
