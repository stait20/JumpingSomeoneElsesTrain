/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- Journey.h				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 12/04/21													*
*	Update Description:	Added lines vector input to contructor				*
*																			*
*****************************************************************************/

#ifndef JOURNEY_HEADER
#define JOURNEY_HEADER

#include "Train.h"
#include <vector>
#include <string>

class Journey
{
private:
	std::vector<Train> trains;
	std::vector<std::string> route;
	// Stores time as a single integer of number of minutes since 00:00
	int depTime;

public:
	Journey(std::vector<std::vector<std::string>>, std::string, std::string, int);
	std::string displayJourney();
	std::vector<std::string> getRoute() { return route; }
	Train getTrain(int);
};


#endif // !JOURNEY_HEADER