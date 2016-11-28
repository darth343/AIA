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
		S_FULL_SPEED = 0,
		S_HALF_SPEED,
		S_STOP,
	};

	enum BUS_SEATS
	{
		B_FULL = 0,
		B_EMPTY,
		B_NONE,
	};

	enum BUS_POS
	{
		P_ONE = 0,
		P_TWO,
		P_THREE,
		P_FOUR,
		P_FIVE,
		P_SIX,
		P_SEVEN,
		P_EIGHT,
	};

	enum BUS_DIRECTIONS
	{
		D_DOWN = 0,
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
	void MovingUp(double dt);
	
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
	BUS_POS BusPosition;
	float timer;											// Timer
	float speed;											// Speed
	int currCommuters;										// Commuters
	const int totalCommuters = 50;							// Total commuters
	Vector3 pos1,											// Positions
			pos2,
			pos3,
			pos4,											
			pos5,
			pos6,
			pos7,
			pos8;
	const int probability = 50;								// Probability for FULL and NOT FULL
	int randomInt;				     						// Random integer
	bool once;												// So that only random once

};



#endif