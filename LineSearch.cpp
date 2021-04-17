/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- LineSearch.cpp		*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 08/04/21													*
*	Update Description:	Changed program to work with strings instead of		*
*	ints																	*
*																			*
*****************************************************************************/



#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <vector>
#include <string>


std::vector<std::string> intersection(std::vector<std::string>& v1, std::vector<std::string>& v2)
{
	// Returns a vector containing all values found in both input vectors
	std::vector<std::string> v3;

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
	return v3;
}

std::vector<int> find_loc_2D(std::vector<std::vector<std::string>> &v, std::string n)
{
	// Returns the row numbers where n is found in the 2D vector, v
	std::vector<std::vector<std::string>>::iterator top_it;

	std::vector<int> found;

	for (top_it = v.begin(); top_it != v.end(); ++top_it)
	{
		std::vector<std::string>::iterator bot_it = std::find(top_it->begin(), top_it->end(), n);
		if (bot_it != top_it->end())
		{
			found.push_back(std::distance(v.begin(), top_it));
		}
	}

	return found;
}

int find_loc_1D(std::vector<std::string> &v, std::string n)
{
	// Returns index value for n in 1D vector, v
	std::vector<std::string>::iterator it = std::find(v.begin(), v.end(), n);

	// If n is not in v, found will equal the v.size()+1
	int found = std::distance(v.begin(), it);
	
	return found;
}


bool check_1st_layer(std::vector<std::vector<std::string>>& v, std::string start, std::string end)
{
	auto start_loc = find_loc_2D(v, start);

	std::vector<int>::iterator it;

	int index;

	// Checks if any rows contain both the start and end value
	for (it = start_loc.begin(); it != start_loc.end(); ++it)
	{
		index = find_loc_1D(v[*it], end);
		if (index < v[*it].size())
		{
			return true;
		}
	}
	return false;
}

std::string check_2nd_layer(std::vector<std::vector<std::string>>& v, std::string start, std::string end)
{
	auto start_loc = find_loc_2D(v, start);
	auto end_loc = find_loc_2D(v, end);

	std::vector<int>::iterator start_it, end_it;
	std::vector<std::string> v1;

	// Checks through all rows containing the start or end values...
	for (start_it = start_loc.begin(); start_it != start_loc.end(); ++start_it)
	{
		for (end_it = end_loc.begin(); end_it != end_loc.end(); ++end_it)
		{
			// If 2 of these rows have another common value, then that value is
			// the station to transfer at
			v1 = intersection(v[*start_it], v[*end_it]);
			if (!v1.empty())
			{
				return v1[0];
			}
		}
	}
	return "";
}

std::vector<std::string> check_3rd_layer(std::vector<std::vector<std::string>> &v, std::string start, std::string end)
{
	auto start_loc = find_loc_2D(v, start);
	auto end_loc = find_loc_2D(v, end);

	std::vector<int>::iterator start_it, end_it;
	std::vector<std::vector<std::string>>::iterator v_it;
	std::vector<std::string> v1, v2, v3;

	// Checks through all rows containing the start or end values...
	for (start_it = start_loc.begin(); start_it != start_loc.end(); ++start_it)
	{
		for (end_it = end_loc.begin(); end_it != end_loc.end(); ++end_it)
		{
			// and checks against all other rows
			for (v_it = v.begin(); v_it != v.end(); ++v_it)
			{
				// Intersection between start row and other row
				v1 = intersection(*v_it, v[*start_it]);
				// Intersection between end row and other row
				v2 = intersection(*v_it, v[*end_it]);

				// If both of these have a value, then those 2 values must be the
				// 2 transfer stations
				if (!v1.empty() && !v2.empty())
				{
					v3.push_back(v1[0]);
					v3.push_back(v2[0]);
					return v3;
				}
			}
		}
	}

	return v3;
}

std::vector<std::string> find_route(std::vector<std::vector<std::string>> &v, std::string start, std::string end)
{
	// Will check for up to 3 layers, this system is very
	// inificient as a lot of the calculations have to be
	// repeated as it checks through the layers
	std::vector<std::string> route = { start };

	if (check_1st_layer(v, start, end))
	{
		route.push_back(end);
		return route;
	}

	std::string n = check_2nd_layer(v, start, end);
	if (n != "")
	{
		route.push_back(n);
		route.push_back(end);
		return route;
	}
	
	std::vector<std::string> v1 = check_3rd_layer(v, start, end);
	if (!v1.empty())
	{
		route.push_back(v1[0]);
		route.push_back(v1[1]);
		route.push_back(end);
		return route;
	}
	return route;
}


