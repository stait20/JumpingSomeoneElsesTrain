#ifndef TICKET_HEADER
#define TICKET_HEADER

#include <vector>
#include <string>

class Ticket
{
private:
	std::vector<std::string> route;
	int noOfChildren;
	int noOfAdults;
	int ticketType;
	int departTime;

public:
	enum journeyType
	{
		Single, Return
	};
	Ticket(std::string start, std::string end, int c, int a, int t, int d);
	std::string getRoute();

};

#endif // !TICKET_HEADER

