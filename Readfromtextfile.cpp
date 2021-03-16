#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

int main()
{
	ifstream file("stationnames.txt");

	vector<std::string> stationnames;

	string input;

	while (file >> input)
	{
		stationnames.push_back(input);
	}

	for (string stationnames : stationnames)
	{
		cout << stationnames << "\n";
	}
}