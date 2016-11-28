#include "Bus.h"


Bus::Bus()
{
	srand(time(NULL));
	BusState = S_FULL_SPEED;
	BusDirection = D_NONE;
	BusPosition = P_ONE;
	timer = 0.f;
	//speed = 45.f;
	speed = 200.f;
	pos1.Set(130, 0, 0);
	pos2.Set(0, 470, 0);
	pos3.Set(540, 0, 0);
	pos4.Set(0, 1000, 0);
	pos5.Set(850, 0, 0);
	pos6.Set(850, 470, 0);
	pos7.Set(1260, 0, 0);
	pos8.Set(0, 1000, 0);
	once = false;
}

Bus::~Bus()
{
}

void Bus::Update(double dt, CMap* m_cMap)
{

	// The bus starts off with moving right with FULL SPEED towards to bus stop 1
	if (BusState == S_FULL_SPEED && BusDirection == D_NONE && BusPosition == P_ONE)
	{
		// Bus move at full speed to the right >
		this->MovingFULL(dt);
		// Generate a random int from 1-100
		randomInt = RandomInteger(1, 100);
		// Generate once only
		once = true;
	}
	
	// When bus reached Bus stop 1
	if (this->position.x >= pos1.x && BusState == S_FULL_SPEED && BusDirection == D_NONE && BusPosition == P_ONE)
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
			// Moving towards bus stop 2
			BusPosition = P_TWO;
		}
	}

	if (this->position.x >= pos1.x && BusState == S_STOP && BusDirection == D_NONE && BusPosition == P_ONE)
	{	
		timer += dt;

		cout << timer << endl;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusDirection = D_DOWN;
			BusPosition = P_TWO;
		}
	}


	// Bus moves down to bus stop 2
	if (BusState == S_FULL_SPEED && BusDirection == D_DOWN && BusPosition == P_TWO)
	{
		timer = 0.f;

		// If bus have yet to reach bus stop 2
		if (this->position.y >= pos2.y)
		{
			// Keep moving down
			this->MovingDown(dt);
		}
		else  // If bus reach bus stop 2
		{
			BusState = S_STOP;
			BusDirection = D_NONE;
			// Roll random int once
			randomInt = RandomInteger(1, 100);
			once = true;

			// If bus is EMPTY
			if (randomInt <= probability)
			{
				cout << "HOHO";
				BusState = S_STOP;
				BusDirection = D_NONE;
				BusPosition = P_TWO;
			}
			else // If bus is FULL
			{
				cout << "HUHU";
				BusState = S_FULL_SPEED;
				BusDirection = D_RIGHT;
				BusPosition = P_THREE;
				cout << BusState << endl;
				cout << BusDirection << endl;
			}
		}
	}

	if (BusState == S_STOP && BusDirection == D_NONE && BusPosition == P_TWO)
	{
		timer += dt;

		cout << timer;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusDirection = D_RIGHT;
			BusPosition = P_THREE;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_RIGHT && BusPosition == P_THREE)
	{
		once = false;
		timer = 0.f;

		if (this->position.x < pos3.x)
		{
			//BusPosition = P_FOUR;
			this->MovingFULL(dt);
		}
		else if (this->position.y < pos4.y)
		{

			BusDirection = D_UP;
			BusPosition = P_FOUR;
		}

	}

	if (BusState == S_FULL_SPEED && BusDirection == D_UP && BusPosition == P_FOUR)
	{
		if (this->position.y < pos4.y)
		{
			this->MovingUp(dt);
		}
		else if (this->position.y >= pos4.y)
		{

			BusDirection = D_RIGHT;
			BusPosition = P_FIVE;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_RIGHT && BusPosition == P_FIVE)
	{
		if (this->position.x < pos5.x)
		{
			this->MovingFULL(dt);
		}
		else
		{
			BusDirection = D_DOWN;
			BusPosition = P_SIX;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_DOWN && BusPosition == P_SIX)
	{
		if (this->position.y > pos6.y)
		{
			this->MovingDown(dt);
		}
		else
		{
			BusDirection = D_RIGHT;
			BusPosition = P_SEVEN;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_RIGHT && BusPosition == P_SEVEN)
	{
		if (this->position.x < pos7.x)
		{
			this->MovingFULL(dt);
		}
		else
		{
			randomInt = RandomInteger(1, 100);

			// If the bus is EMPTY, state change to STOP
			if (randomInt <= probability)
			{
				BusState = S_STOP;
				cout << "KEK" << endl;
			}
			else  // The bus is FULL
			{
				BusDirection = D_UP;
				BusPosition = P_EIGHT;
			}

			once = true;
		}
	}

	if (BusState == S_STOP && BusDirection == D_RIGHT && BusPosition == P_SEVEN)
	{
		timer += dt;
		cout << timer << endl;

		if (timer > 3.0f)
		{
			BusDirection = D_UP;
			BusPosition = P_EIGHT;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_UP && BusPosition == P_EIGHT)
	{
		once = false;
		timer = 0;

		if (this->position.y < pos8.y)
		{
			this->MovingUp(dt);
		}
		else
		{
			randomInt = RandomInteger(1, 100);
			once = true;

			// If the bus is EMPTY, state change to STOP
			if (randomInt <= probability)
			{
				BusState = S_STOP;
				cout << "HUEHUE" << endl;
			}
			else  // The bus is FULL
			{
				this->MovingFULL(dt);
			}
		}

	}

	if (BusState == S_STOP && BusDirection == D_UP && BusPosition == P_EIGHT)
	{
		timer += dt;
		cout << timer << endl;

		if (timer > 3.0f)
		{
			this->MovingFULL(dt);
		}
	}

	// Reset bus to original position
	if (this->position.x > 1400)
	{
		this->position.x = 10;
		BusState = S_FULL_SPEED;
		BusDirection = D_NONE;
		BusPosition = P_ONE;
		once = false;
		timer = 0;
	}
	
}

void Bus::MovingUp(double dt)
{
	this->position.y += speed * dt;
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