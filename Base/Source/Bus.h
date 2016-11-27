#ifndef BUS_H
#define BUS_H

#include "GameObject.h"
//#include "Traffic.h"

#include <time.h>     // time
#include <stdio.h>    // NULL
#include <stdlib.h>   // srand, rand

class Bus : public GameObject
{
public:

	enum BUS_STATES
	{
		S_FULL_SPEED,
		S_HALF_SPEED,
		S_STOP,
	};

	enum BUS_SEATS
	{
		B_FULL,
		B_EMPTY,
		B_NONE,
	};

	enum BUS_DIRECTIONS
	{
		D_DOWN,
		D_UP,
		D_RIGHT,
		D_NONE,								   // Moving straight
	};

	Bus();
	~Bus();

	// Bus update
	virtual void Update(double dt, CMap* m_cMap = NULL);

	void MovingFULL(double dt);                   // Move the bus at full speed
	void MovingHALF(double dt);					  // Move the bus at half speed	

	void MovingDown(double dt);

	void rollNum();								  // Randomly generate a number for probabilty


	// Getters and setters
	int GetCommuters();
	void SetCommuters(int x);
	float GetSpeed();
	void SetSpeed(float x);


	// Test
	int RandomInteger(int lowerLimit, int upperLimit);

private:

	BUS_STATES BusState;									// Bus state
	BUS_DIRECTIONS  BusDirection;							// Bus direction state
	float timer;											// Timer
	float speed;											// Speed
	int currCommuters;										// Commuters
	const int totalCommuters = 50;							// Total commuters
	Vector3 busStop1, busStop2, busStop3, busStop4;			// Positions of bus stop 1 and 2
	const int probability = 50;								// Probability for FULL and NOT FULL
	int randomInt;				     						// Random integer
	bool once;												// So that only random once

};



#endif