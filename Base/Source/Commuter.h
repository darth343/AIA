#pragma once
#include "GameObject.h"
#include "Pathfinder.h"

class Commuter : public GameObject
{
public:
	Commuter();
	~Commuter();
	enum STATES
	{
		WALK,
		RUN,
		LEAVE,
		WAIT,
	};
	virtual void Update(double dt, CMap* map);
	void Move(double dt, int TileSize);
	bool isBusNearby();
	STATES getState()
	{
		return state;
	}

private:
	float timer;
	const float waitLimit = 5;
	const int speed = 100;
	bool nearestBusStopFound;
	Tile nearestBusStop;
	Tile nextTile;
	STATES state;
	Pathfinder pathfinder;
};

