#include "Ticket.h"
#include "LineSearch.h"

Ticket::Ticket(std::string start, std::string end, int c, int a, int t, int d)
{
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

	route = find_route(v, start, end);
	noOfChildren = c;
	noOfAdults = a;
	ticketType = t;
	departTime = d;
}

std::string Ticket::getRoute()
{
	std::string route_string = "";
	for (std::string s : route)
	{
		route_string += s;
		route_string += "-";
	}
	return route_string;
}
