/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- cApp.h				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 23/02/21													*
*	Update Description:	Added basic wxWidgets framework to display GUI		*
*																			*
*****************************************************************************/

#ifndef APP_HEADER
#define APP_HEADER

#include "wx/wx.h"
#include "cMain.h"

class cApp : public wxApp
{
public:
	cApp();
	~cApp();
private:
	cMain* m_frame1 = nullptr;

public:
	virtual bool OnInit();
	
};

#endif