#include "Line.h"

#include <cstdlib> 
#include <ctime>



Line::Line(std::vector<std::string> v, int t)
{
	
	if (t == 0)
	{
		srand((unsigned int)time(NULL));
		travelTime = rand() % 15 + 15;
	}
	else
	{
		travelTime = t;
	}
	stations = v;
}
