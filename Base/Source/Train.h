#ifndef TRAIN_H
#define TRAIN_H

#include "GameObject.h"

#include <time.h>     // time
#include <stdio.h>    // NULL
#include <stdlib.h>   // srand, rand

class Train : public GameObject
{
public:

	enum TRAIN_STATES
	{
		S_STOP = 0,
		S_OPEN,
		S_CLOSE,
		S_MOVE,
	};

	enum TRAIN_POS
	{
		P_TO = 0,
		P_FROM,
		P_NONE,
	};

	Train();
	~Train();

	virtual void TrainUpdate(double dt);
	// Checks if all the commuters have boarded and all the commuters have alighted
	bool checkTrainIsReady();

	// Getters and setters
	void setCommutersBoarded(int x);
	int getCommutersBoarded();
	void setCommutersAlighted(int x);
	int getCommutersAlighted();
	int getTrainPosState();
	void setTrainPosState(int x);
	int getTrainState();
	float getTimer();

	// Train move TO endPos
	void MoveTO(double dt);
	// Train move FROM endPos
	void MoveFROM(double dt);

	

private:
	TRAIN_STATES TrainState;
	TRAIN_POS    TrainPos;
	float timer;							// Timer 
	const float speed = 800.f;				// Train speed
	const int maxCommuters = 500;			// Max commuters on the train
	Vector3 trainPos, stationPos, endPos;   // Positions
	int commBoarding;						// Number of commuters boarding
	int commAlighting;						// Number of commuters alighting
	bool open;								// 

};



#endif