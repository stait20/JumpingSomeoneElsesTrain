#ifndef TRAIN_HEADER
#define TRAIN_HEADER

class Train 
{
private:
	int** trainArr;
	int height = 8;
	int width = 2;

public:
	// Enum type to show whether a seat is booked, unavailible or available
	enum Seat
	{
		Booked, Unavailable, Available
	};
	Train();
	virtual ~Train();
	int getHeight() { return height; }
	int getWidth() { return width; }
	void updateDistance();
	int checkSeat(int x, int y);
};


#endif