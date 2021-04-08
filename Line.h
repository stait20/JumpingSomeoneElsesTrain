#ifndef LINE_HEADER
#define LINE_HEADER

#include <vector>
#include <string>

class Line
{
private:
	std::vector<std::string> stations;
	int travelTime;

public:

	Line(std::vector<std::string> v, int t);

};

#endif // !LINE_HEADER

