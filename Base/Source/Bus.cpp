#include "Bus.h"


Bus::Bus()
{
	srand(time(NULL));
	BusState = S_FULL_SPEED;
	BusDirection = D_NONE;
	BusPosition = P_ONE;
	timer = 0.f;
	pos1.Set(130, 0, 0);
	pos2.Set(0, 470, 0);
	pos3.Set(540, 0, 0);
	pos4.Set(540, 1000, 0);
	pos5.Set(850, 1000, 0);
	pos6.Set(850, 470, 0);
	pos7.Set(1260, 0, 0);
	pos8.Set(1260, 1000, 0);
	once = false;
	once2 = false;
	once3 = false;
}

Bus::~Bus()
{
}

void Bus::Update(double dt, CMap* m_cMap)
{
	if (once2 == false)
	{
		randomInt2 = rand() % 100;
		cout << randomInt2 << endl;
		once2 = true;
	}

	if (randomInt2 <= probability)
	{
		UpdateTurning(dt);
	}
	else
	{
		UpdateStraight(dt);
	}
}

void Bus::UpdateTurning(double dt)
{
	// The bus starts off with moving right with FULL SPEED towards to bus stop 1
	if (BusState == S_FULL_SPEED && BusDirection == D_NONE && BusPosition == P_ONE)
	{
		// Bus move at full speed to the right >
		this->MovingRight(dt, fullSpeed);
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
			// Empty bus, state change to stop
			BusState = S_STOP;
		}
		else // If the rolled int is BIGGER than 50
		{
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
			this->MovingDown(dt, fullSpeed);
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
				BusState = S_STOP;
				BusDirection = D_NONE;
				BusPosition = P_TWO;
			}
			else // If bus is FULL
			{
				BusState = S_FULL_SPEED;
				BusDirection = D_RIGHT;
				BusPosition = P_THREE;
			}
		}
	}

	if (BusState == S_STOP && BusDirection == D_NONE && BusPosition == P_TWO)
	{
		timer += dt;

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
			this->MovingRight(dt, fullSpeed);
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
			this->MovingUp(dt, fullSpeed);
		}
		else if (this->position.y >= pos4.y)
		{
			BusState = S_HALF_SPEED;
			BusDirection = D_RIGHT;
			BusPosition = P_FIVE;
		}
	}

	if (BusState == S_HALF_SPEED && BusDirection == D_RIGHT && BusPosition == P_FIVE)
	{
		if (this->position.x < pos5.x)
		{
			this->MovingRight(dt, halfSpeed);
		}
		else
		{
			BusState = S_FULL_SPEED;
			BusDirection = D_DOWN;
			BusPosition = P_SIX;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_DOWN && BusPosition == P_SIX)
	{
		if (this->position.y > pos6.y)
		{
			this->MovingDown(dt, fullSpeed);
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
			this->MovingRight(dt, fullSpeed);
		}
		else // Reached position 7
		{
			randomInt = RandomInteger(1, 100);
			once = true;

			// If the bus is EMPTY, state change to STOP
			if (randomInt <= probability)
			{
				BusState = S_STOP;
			}
			else  // The bus is FULL
			{
				BusDirection = D_UP;
				BusPosition = P_EIGHT;
			}
		}
	}

	if (BusState == S_STOP && BusDirection == D_RIGHT && BusPosition == P_SEVEN)
	{
		timer += dt;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusDirection = D_UP;
			BusPosition = P_EIGHT;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_UP && BusPosition == P_EIGHT)
	{
		once = false;
		timer = 0.f;
		// Bus move up to reach position 8
		if (this->position.y < pos8.y)
		{
			this->MovingUp(dt, fullSpeed);
		}
		else // Bus reached position 8
		{
			randomInt = RandomInteger(1, 100);
			once = true;

			// If the bus is EMPTY, state change to STOP
			if (randomInt <= probability)
			{
				BusState = S_STOP;
			}
			else  // The bus is FULL
			{
				BusState = S_FULL_SPEED;
				BusDirection = D_RIGHT;
				BusPosition = P_END;
				this->MovingRight(dt, fullSpeed);
			}
		}
	}

	if (BusState == S_STOP && BusDirection == D_UP && BusPosition == P_EIGHT)
	{
		timer += dt;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusDirection = D_RIGHT;
			BusPosition = P_END;
		}
	}

	if (BusState == S_FULL_SPEED && BusDirection == D_RIGHT && BusPosition == P_END)
	{
		this->MovingRight(dt, fullSpeed);
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
		once2 = false;
	}

}

void Bus::UpdateStraight(double dt)
{

	// The bus moves to bus stop 1
	if (BusState == S_FULL_SPEED && BusDirection == D_NONE && BusPosition == P_ONE)
	{
		// If bus havent reach bus stop 1
		if (this->position.x < pos1.x)
		{
			this->MovingRight(dt, fullSpeed);
		}
		else // If bus reach bus stop 1
		{
			randomInt = (rand() % 100);
			once = true;

			// If bus is EMPTY
			if (randomInt <= probability)
			{
				BusState = S_STOP;
			}
			else // If bus is FULL
			{
				BusState = S_FULL_SPEED;
				BusPosition = P_FOUR;
				BusDirection = D_RIGHT;
			}
		}
	}

	// When bus is empty, state is stop and then after 3 sec move again
	if (BusState == S_STOP && BusDirection == D_NONE && BusPosition == P_ONE)
	{

		timer += dt;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusPosition = P_FOUR;
			BusDirection = D_RIGHT;
		}
	}


	// Bus going to position 4
	if (BusState == S_FULL_SPEED, BusPosition == P_FOUR, BusDirection == D_RIGHT)
	{
		if (this->position.x < pos4.x)
		{
			this->MovingRight(dt, fullSpeed);
		}
		else
		{
			BusState = S_HALF_SPEED;
			BusPosition = P_FIVE;
			BusDirection = D_RIGHT;

		}
	}

	// Bus going to position 5
	if (BusState == S_HALF_SPEED && BusPosition == P_FIVE && BusDirection == D_RIGHT)
	{
		if (this->position.x < pos5.x)
		{
			this->MovingRight(dt, halfSpeed);
		}
		else
		{
			BusState = S_FULL_SPEED;
			BusPosition = P_EIGHT;
			BusDirection = D_RIGHT;
			once = false;
		}
	}


	if (BusState == S_FULL_SPEED && BusPosition == P_EIGHT && BusDirection == D_RIGHT)
	{
		if (this->position.x < pos8.x)
		{
			this->MovingRight(dt, fullSpeed);
		}
		else
		{
			if (once3 == false)
			{
				randomInt3 = rand() % 100;
				once3 = true;
			}
			
			// If bus is EMPTY
			if (randomInt3 < probability)
			{
				BusState = S_STOP;
			}
			else   // If bus is FULL
			{
				BusState = S_FULL_SPEED;
				BusPosition = P_END;
				BusDirection = D_RIGHT;
			}

		}
	}
	
	if (BusState == S_STOP && BusPosition == P_EIGHT && BusDirection == D_RIGHT)
	{
		timer += dt;

		cout << timer << endl;

		if (timer > 3.0f)
		{
			BusState = S_FULL_SPEED;
			BusPosition = P_END;
			BusDirection = D_RIGHT;
		}
	}


	if (BusState == S_FULL_SPEED && BusPosition == P_END && BusDirection == D_RIGHT)
	{
		this->MovingRight(dt, fullSpeed);
	}

	// When the bus get out of screen, make the bus appear on the left side of the screen again
	if (BusState == S_FULL_SPEED && BusPosition == P_END && BusDirection == D_RIGHT)
	{
		this->MovingRight(dt, fullSpeed);
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
		once2 = false;
		once3 = false;
	}
}

void Bus::MovingUp(double dt, float speed)
{
	this->position.y += speed * dt;
}

void Bus::MovingDown(double dt, float speed)
{
	this->position.y -= speed * dt;
}

int Bus::RandomInteger(int lowerLimit, int upperLimit)
{
	return rand() % (upperLimit - lowerLimit + 1) + lowerLimit;
}

int Bus::GetCommuters()
{
	return currCommuters;
}

void Bus::SetCommuters(int x)
{
	this->currCommuters = x;
}

void Bus::MovingRight(double dt, float speed)
{
	this->position.x += speed * dt;
}

int Bus::getState()
{
	if (BusState == S_FULL_SPEED)
		return 0;
	if (BusState == S_HALF_SPEED)
		return 1;
	if (BusState == S_STOP)
		return 2;
}