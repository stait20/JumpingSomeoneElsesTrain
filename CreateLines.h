/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- CreateLines.h			*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 12/04/21													*
*	Update Description:	Added Glasgow to Edinburgh line						*
*																			*
*****************************************************************************/

#ifndef LINES_HEADER
#define LINES_HEADER

#include <vector>
#include <string>

std::vector<std::vector<std::string>> CreateLines()
{
	std::vector<std::string> L1 = { "Wick","Inverness" };
	std::vector<std::string> L2 = { "Inverness","Aberdeen" };
	std::vector<std::string> L3 = { "Aberdeen","Dundee","Perth","Stirling","Glasgow" };
	std::vector<std::string> L4 = { "Aberdeen","Dundee","Edinburgh" };
	std::vector<std::string> L5 = { "Inverness","Perth","Stirling","Glasgow" };
	std::vector<std::string> L6 = { "Inverness","Perth","Stirling","Edinburgh" };
	std::vector<std::string> L7 = { "Glasgow","Fort William" };
	std::vector<std::string> L8 = { "Glasgow","Carlisle" };
	std::vector<std::string> L9 = { "Edinburgh","Carlisle" };
	std::vector<std::string> L10 = { "Glasgow","Edinburgh" };

	std::vector<std::vector<std::string>> LinesVec;

	LinesVec.push_back(L1);
	LinesVec.push_back(L2);
	LinesVec.push_back(L3);
	LinesVec.push_back(L4);
	LinesVec.push_back(L5);
	LinesVec.push_back(L6);
	LinesVec.push_back(L7);
	LinesVec.push_back(L8);
	LinesVec.push_back(L9);
	LinesVec.push_back(L10);

	return LinesVec;

}

#endif // All stations for dropdown menu
