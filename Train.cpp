#include "Train.h"
#include <cstdlib> 
#include <ctime>
#include <fstream>

Train::Train()
{
	// Creates 2D dynamic array to represent train
	trainArr = new int* [height];
	for (int i = 0; i < height; i++) {
		trainArr[i] = new int[width * 2];
	}

	// Randomly decides if seats are booked or not
	srand((unsigned int)time(NULL));
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width * 2; j++) {
			if (rand() % 2 == 1)
			{
				trainArr[i][j] = Booked;
			}
			else
			{
				trainArr[i][j] = Available;
			}
		}
	}
	
	// Runs function to add in unavailable seats
	updateDistance();
}

Train::~Train()
{
	// Destructor for 2D dynamic array
	for (int i = 0; i < height; ++i) {
		delete[] trainArr[i];
	}

	delete[] trainArr;
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
