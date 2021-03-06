#include "Train.h"

Train::Train()
{
	srand(time(NULL));
	TrainState = S_STOP;
	TrainPos = P_NONE;
	timer = 0.f;
	open = false;
}

Train::~Train()
{
}

void Train::TrainUpdate(double dt)
{
	timer += dt;

	// Stop state to Open state after 3 seconds
	if (timer > 3.f && TrainState == S_STOP)
	{
		timer = 0;
		TrainState = S_OPEN;  // open
		// RNG 1 time only for commuters when at Open state
		getCommutersBoarded();
		getCommutersAlighted();
		open = true;
	}

	// Open state
	if (open && TrainState == S_OPEN)
	{
		if (commAlighting != 0)
		{
			commAlighting--;
		}

		if (commBoarding != 0)
		{
			commBoarding--;
		}

		// When no more boarding or alighting commuters
		if (checkTrainIsReady() == true)
		{
			TrainState = S_CLOSE;
			timer = 0;
		}
	}

	// Close state and after 2 seconds
	if (TrainState == S_CLOSE && timer > 2.f)
	{
		open = false;
		// Change to Move state and reset timer to 0
		TrainState = S_MOVE;
		timer = 0;
		// Change NONE state to TO state
		TrainPos = P_TO;
	}


	// At Move state
	if (TrainState == S_MOVE && timer > 31.f)
	{
		// Change state back to Stop state and reset timer to 0
		TrainState = S_STOP;
		timer = 0;
		TrainPos = P_NONE;
	}
	
}

bool Train::checkTrainIsReady()
{
	if (commBoarding == 0 && commAlighting == 0)
		return true;
	else
		return false;
}

void Train::setCommutersBoarded(int x)
{
	this->commBoarding = x;
}

int Train::getCommutersBoarded()
{
	return ( commBoarding = (rand() % maxCommuters) );
}

void Train::setCommutersAlighted(int x)
{
	this->commAlighting = x;
}

int Train::getCommutersAlighted()
{
	return (commAlighting = (rand() % maxCommuters));
}

void Train::MoveTO(double dt)
{
	this->position.x += speed * dt * 0.1f;
}

void Train::MoveFROM(double dt)
{
	this->position.x -= speed * dt * 0.1f;
}

int Train::getTrainPosState()
{
	if (TrainPos == P_TO)
		return 0;
	if (TrainPos == P_FROM)
		return 1;
	if (TrainPos == P_NONE)
		return 2;
}

void Train::setTrainPosState(int x)
{
	if (x == 0)
		this->TrainPos = P_TO;
	if (x == 1)
		this->TrainPos = P_FROM;
	if (x == 2)
		this->TrainPos = P_NONE;
}

int Train::getTrainState()
{
	if (TrainState == S_STOP)
		return 0;
	if (TrainState == S_OPEN)
		return 1;
	if (TrainState == S_CLOSE)
		return 2;
	if (TrainState == S_MOVE)
		return 3;
}

float Train::getTimer()
{
	return timer;
}