#include "Journey.h"
#include "LineSearch.h"

Journey::Journey(std::string depStation, std::string arrStation, int t)
{
	// Temp network info
	std::vector<std::vector<std::string>> v;
	std::vector<std::string> v1, v2, v3;

	v1.push_back("Glasgow");
	v1.push_back("Edinburgh");

	v2.push_back("Edinburgh");
	v2.push_back("Stirling");
	v2.push_back("Inverness");

	v3.push_back("Inverness");
	v3.push_back("John O'Groats");

	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);

	route = find_route(v, depStation, arrStation);

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
