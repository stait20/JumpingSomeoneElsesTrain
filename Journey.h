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
	int depTime;

public:
	Journey(std::vector<std::vector<std::string>>, std::string, std::string, int);
	std::string displayJourney();
	std::vector<std::string> getRoute() { return route; }
	Train getTrain(int);
};


#endif // !JOURNEY_HEADER