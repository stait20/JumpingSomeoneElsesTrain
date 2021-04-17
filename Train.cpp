/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- Train.cpp				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 08/04/21													*
*	Update Description:	Changed trainArr to be a 2D vector					*
*																			*
*****************************************************************************/

#include "Train.h"
#include <cstdlib> 
#include <ctime>
#include <fstream>

Train::Train()
{
	// Create temporary vector
	std::vector<int> v;
	
	// Randomly decides if seats are booked or not
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * 2; j++) {
			if (rand() % 3 == 1)
			{
				v.push_back(Booked);
			}
			else
			{
				v.push_back(Available);
			}
		}
		// Adds temp vector to 2D train vector
		trainArr.push_back(v);
		// Clears temp vector so it can be used again
		v.clear();
	}
	
	// Runs function to add in unavailable seats
	updateDistance();
}


void Train::updateDistance()
{
	// Checks to find what seats need to be made unavailable
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * 2; j++) {
			// Will look at every booked seat
			if (trainArr[i][j] == Booked)
			{
				// Checks if seat next to it is currently available
				// The mod functions checks whether the seat to the right 
				// or the left needs to be considered
				if (j % 2 == 1 && trainArr[i][j-1] == Available)
				{
					// If so makes it unavailable
					trainArr[i][j - 1] = Unavailable;
				}
				else if (j % 2 == 0 && trainArr[i][j+1] == Available)
				{
					trainArr[i][j + 1] = Unavailable;
				}
			}
		}
	}
}

int Train::checkSeat(int x, int y)
{
	return trainArr[x][y];
}
