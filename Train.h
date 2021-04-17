#ifndef TRAIN_HEADER
#define TRAIN_HEADER

/****************************************************************************
*																			*
*	EE273 - Group 34 - Jumping Someone Else's Train	- Train.h				*
*																			*
*	Sam Tait & Frazer Murray												*
*																			*
*	Last Updated: 08/04/21													*
*	Update Description:	Changed trainArr to be a 2D vector					*
*																			*
*****************************************************************************/

#include <vector>

class Train 
{
private:
	std::vector<std::vector<int>> trainArr;
	int height = 8;
	int width = 2;

public:
	// Enum type to show whether a seat is booked, unavailible or available
	enum Seat
	{
		Booked, Unavailable, Available
	};
	Train();
	virtual ~Train() {}
	int getHeight() { return height; }
	int getWidth() { return width; }
	void updateDistance();
	int checkSeat(int x, int y);
};


#endif