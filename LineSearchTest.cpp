/****************************************************************************
*																			*
*	This code is a possible solution to finding transfer stations for more  *
*	complex journeys.														*
*	This solution is not remotely elegent or efficient, and currently		*
*	it only works with journeys up to 2 transfers, but I imagine that		*
*	could be expanded.														*
*																			*
*	It makes uses numbers to represent stations, but this could be easily	*
*	changed to just contain the actual station names						*
*	These stations are stored in a 2D vector to represent the different		*
*	lines.																	*
*																			*
*****************************************************************************/



#include <algorithm>
#include <iostream>
#include <cstdlib> 
#include <ctime>
#include <vector>


std::vector<int> intersection(std::vector<int>& v1, std::vector<int>& v2)
{
	// Returns a vector containing all values found in
	// both input vectors
	std::vector<int> v3;

	std::sort(v1.begin(), v1.end());
	std::sort(v2.begin(), v2.end());

	std::set_intersection(v1.begin(), v1.end(), v2.begin(), v2.end(), back_inserter(v3));
	return v3;
}

std::vector<int> find_loc_2D(std::vector<std::vector<int>> &v, int n)
{
	// Returns the row numbers where n is found in the 2D vector, v
	std::vector<std::vector<int>>::iterator top_it;

	std::vector<int> found;

	for (top_it = v.begin(); top_it != v.end(); ++top_it)
	{
		std::vector<int>::iterator bot_it = std::find(top_it->begin(), top_it->end(), n);
		if (bot_it != top_it->end())
		{
			found.push_back(std::distance(v.begin(), top_it));
		}
	}

	return found;
}

int find_loc_1D(std::vector<int> &v, int n)
{
	// Returns index value for n in 1D vector, v
	std::vector<int>::iterator it = std::find(v.begin(), v.end(), n);

	// If n is not in v, found will equal the v.size()+1
	int found = std::distance(v.begin(), it);
	
	return found;
}


bool check_1st_layer(std::vector<std::vector<int>>& v, int start, int end)
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

int check_2nd_layer(std::vector<std::vector<int>>& v, int start, int end)
{
	auto start_loc = find_loc_2D(v, start);
	auto end_loc = find_loc_2D(v, end);

	std::vector<int>::iterator start_it, end_it;
	std::vector<int> v1;

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
	return NULL;
}

std::vector<int> check_3rd_layer(std::vector<std::vector<int>> &v, int start, int end)
{
	auto start_loc = find_loc_2D(v, start);
	auto end_loc = find_loc_2D(v, end);

	std::vector<int>::iterator start_it, end_it;
	std::vector<std::vector<int>>::iterator v_it;
	std::vector<int> v1, v2, v3;

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

std::vector<int> find_route(std::vector<std::vector<int>> &v, std::vector<int> &route, int start, int end)
{
	// Will check for up to 3 layers, this system is very
	// inificient as a lot of the calculations have to be
	// repeated as it checks through the layers
	if (check_1st_layer(v, start, end))
	{
		route.push_back(end);
		return route;
	}

	int n = check_2nd_layer(v, start, end);
	if (n != NULL)
	{
		route.push_back(n);
		route.push_back(end);
		return route;
	}
	
	std::vector<int> v1 = check_3rd_layer(v, start, end);
	if (!v1.empty())
	{
		route.push_back(v1[0]);
		route.push_back(v1[1]);
		route.push_back(end);
		return route;
	}
	return route;
}


std::vector<std::vector<int>> rand_lines()
{
	// Creates random lines
	srand((unsigned int)time(NULL));

	std::vector<int> v1, v2, v3, v4, v5, v6, v7, v8, v9;
	std::vector<std::vector<int>> v;

	int n, a, b;

	a = 70; // Range of random values
	b = 1; // Minimum random values
	// i.e. values will be between b and b+a-1

	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v1.begin(), v1.end(), n);
		if (it == v1.end())
		{
			v1.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v2.begin(), v2.end(), n);
		if (it == v2.end())
		{
			v2.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v3.begin(), v3.end(), n);
		if (it == v3.end())
		{
			v3.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v4.begin(), v4.end(), n);
		if (it == v4.end())
		{
			v4.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v5.begin(), v5.end(), n);
		if (it == v5.end())
		{
			v5.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v6.begin(), v6.end(), n);
		if (it == v6.end())
		{
			v6.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v7.begin(), v7.end(), n);
		if (it == v7.end())
		{
			v7.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v8.begin(), v8.end(), n);
		if (it == v8.end())
		{
			v8.push_back(n);
		}
	}
	for (int i = 0; i < 10; i++)
	{
		n = rand() % a + b;
		std::vector<int>::iterator it = std::find(v9.begin(), v9.end(), n);
		if (it == v9.end())
		{
			v9.push_back(n);
		}
	}
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);
	v.push_back(v4);
	v.push_back(v5);
	v.push_back(v6);
	v.push_back(v7);
	v.push_back(v8);
	v.push_back(v9);

	return v;
}



int main() 
{

	// Uncomment to use random lines
	//std::vector<std::vector<int>> v;
	//v = rand_lines();

	std::vector<int> v1, v2, v3, v4;

	v1 = { 1, 3, 9, 5 };
	v2 = { 4, 3, 2, 6 };
	v3 = { 8, 11, 6, 7 };

	std::vector<std::vector<int>> v;
	v.push_back(v1);
	v.push_back(v2);
	v.push_back(v3);


	// Prints out all lines
	for (std::vector<int> n1 : v)
	{
		for (int n2 : n1)
		{
			std::cout << n2 << ' ';
		}
		std::cout << '\n';
	}

	std::cout << '\n';

	int start, end;

	// Recieves start and end station from user
	std::cout << "Enter starting location: ";
	std::cin >> start;
	std::cout << "Enter end location: ";
	std::cin >> end;

	std::vector<int> route = { start };

	// Finds route with anything up to 2 line changes
	std::vector<int> found = find_route(v, route, start, end);

	// outputs route
	for (int n : found)
	{
		std::cout << n << ' ';
	}
}



