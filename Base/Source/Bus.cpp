#include "Bus.h"


Bus::Bus()
{
	srand(time(NULL));
	BusState = S_FULL_SPEED;
	BusDirection = D_NONE;
	timer = 0.f;
	speed = 45.f;
	busStop1.Set(130, 0, 0);
	busStop2.Set(0, 470, 0);
	once = false;
}

Bus::~Bus()
{
}

void Bus::Update(double dt, CMap* m_cMap)
{
	timer += dt;

	// The bus starts off with moving right with FULL SPEED
	if (BusState == S_FULL_SPEED && BusDirection == D_NONE)
	{
		// Bus move at full speed to the right >
		this->MovingFULL(dt);
		// Generate a random int from 1-100
		randomInt = RandomInteger(1, 100);
		// Generate once only
		once = true;
	}
	
	// When bus reached Bus stop 1
	if (this->position.x >= busStop1.x && BusState == S_FULL_SPEED && BusDirection == D_NONE)
	{
		once = false;

		// If the rolled int is SMALLER or equals to 50
		if (randomInt <= probability)
		{
			cout << "hehe";
			// Empty bus, state change to stop
			BusState = S_STOP;
		}
		else // If the rolled int is BIGGER than 50
		{
			cout << "haha";
			// Full bus, state doesnt change
			BusState = S_FULL_SPEED;
			// Direction change
			BusDirection = D_DOWN;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_DOWN)
	{
		if (this->position.y >= busStop2.y)
		{
			this->MovingDown(dt);
		}
		else  // If bus reach bus stop 2
		{
			BusState = S_STOP;
			BusDirection = D_NONE;
			// Roll random int once
			randomInt = RandomInteger(1, 100);
			once = true;
		}
	}

	if (BusState == S_STOP && BusDirection == D_NONE)
	{
		if (randomInt <= probability)
		{
			cout << "HOHO";
			BusState = S_STOP;
			BusDirection = D_NONE;
		}
		else
		{
			cout << "HUHU";
			this->MovingFULL(dt);
		}
	}
	

	
	
}

void Bus::MovingDown(double dt)
{
	this->position.y -= speed * dt;
}

int Bus::RandomInteger(int lowerLimit, int upperLimit)
{
	return rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
}

void Bus::rollNum()
{

}

int Bus::GetCommuters()
{
	return currCommuters;
}

void Bus::SetCommuters(int x)
{
	this->currCommuters = x;
}

float Bus::GetSpeed()
{
	return speed;
}

void Bus::SetSpeed(float x)
{
	this->speed = x;
}

void Bus::MovingFULL(double dt)
{
	this->position.x += speed * dt;
}