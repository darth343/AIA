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
		P_END,
		P_MID1,
		P_MID2,
	};

	enum BUS_DIRECTIONS
	{
		D_DOWN = 0,
		D_UP,
		D_RIGHT,
		D_NONE,								  
	};

	Bus();
	~Bus();

	// Bus update
	virtual void Update(double dt, CMap* m_cMap = NULL);
	void UpdateTurning(double dt);							// Update when the bus take the turning path
	void UpdateStraight(double dt);							// Update when the bus take the straight path

	void MovingRight(double dt, float speed);                  
	void MovingDown(double dt, float speed);
	void MovingUp(double dt, float speed);

	// Getters and setters
	int GetCommuters();
	void SetCommuters(int x);
	int getState();


	// Test
	int RandomInteger(int lowerLimit, int upperLimit);

private:

	BUS_STATES BusState;									// Bus state
	BUS_DIRECTIONS  BusDirection;							// Bus direction state
	BUS_POS BusPosition;									// Bus pos
	float timer;											// Timer
	const float fullSpeed = 500.f,							// Speeds
				halfSpeed = 250.f;						
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
	int randomInt, randomInt2, randomInt3;				    // Random integer
	bool once;												// So that only random once
	bool once2;
	bool once3;

};



#endif