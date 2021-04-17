/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- Journey.cpp			*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 12/04/21													*
*	Update Description:	Removed tempory lines, now gets lines input			*
*	externally																*
*																			*
*****************************************************************************/

#include "Journey.h"
#include "LineSearch.h"

Journey::Journey(std::vector<std::vector<std::string>> lines, std::string depStation, std::string arrStation, int t)
{
	// Find route
	route = find_route(lines, depStation, arrStation);

	// Create vector of Train objects
	for (int i = 0; i < route.size() - 1; i++)
	{
		trains.push_back(Train());
	}

	depTime = t;
}

std::string Journey::displayJourney()
{
	return std::string();
}

Train Journey::getTrain(int n)
{
	return trains[n];
}
