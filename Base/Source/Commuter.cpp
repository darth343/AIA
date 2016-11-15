#include "Commuter.h"


Commuter::Commuter()
: nearestBusStopFound(false)
, state(WALK)
, timer(0)
{
}


Commuter::~Commuter()
{
}


void Commuter::Update(double dt, CMap* m_cMap)
{
	switch (state)
	{
	case WALK:
	{
				 if (!pathfinder.found)
				 {
					 Vector3 TilePos;
					 TilePos.x = position.x / m_cMap->GetTileSize();
					 TilePos.y = position.y / m_cMap->GetTileSize();
					 if (!nearestBusStopFound)
					 {
						 Vector3 lowestdist = Vector3(9999, 9999, 0);
						 for (int i = 0; i < m_cMap->BusStops.size(); i++)
						 {
							 Vector3 dist = TilePos - m_cMap->BusStops[i].Pos;
							 if (lowestdist.Length() > dist.Length())
							 {
								 nearestBusStop = m_cMap->BusStops[i];
								 lowestdist = dist;
							 }
						 }
						 nearestBusStopFound = true;
					 }
					 pathfinder.FindPath(m_cMap->theMap[TilePos.y][TilePos.x], nearestBusStop, m_cMap);
					 if (pathfinder.found)
					 {
						 nextTile = pathfinder.pathToEnd.back();
					 }
				 }
				 else
				 {
					 Move(dt, m_cMap->GetTileSize());
				 }
	}
		break;
	case RUN:
		break;
	case LEAVE:
		if (!pathfinder.found)
		{
			Vector3 TilePos;
			TilePos.x = position.x / m_cMap->GetTileSize();
			TilePos.y = position.y / m_cMap->GetTileSize();
			pathfinder.FindPath(m_cMap->theMap[TilePos.y][TilePos.x], m_cMap->theMap[0][0], m_cMap);
			if (pathfinder.found)
			{
				nextTile = pathfinder.pathToEnd.back();
			}
		}
		else
		{
			Move(dt, m_cMap->GetTileSize());
			if (isBusNearby())
			{
				state = WALK;
			}
		}
		break;
	case WAIT:
		timer += dt;
		if (timer > waitLimit)
		{
			timer = 0;
			state = LEAVE;
		}
		break;

	}
}

void Commuter::Move(double dt, int TileSize)
{
	if (nextTile.Pos.x * TileSize < position.x)
	{
		position.x -= dt * speed;
		if (nextTile.Pos.x * TileSize > position.x)
		{
			position.x = nextTile.Pos.x * TileSize;
		}
	}
	else if (nextTile.Pos.x * TileSize > position.x)
	{
		position.x += dt * speed;
		if (nextTile.Pos.x * TileSize < position.x)
		{
			position.x = nextTile.Pos.x * TileSize;
		}
	}
	if (nextTile.Pos.y * TileSize < position.y)
	{
		position.y -= dt * speed;
		if (nextTile.Pos.y * TileSize > position.y)
		{
			position.y = nextTile.Pos.y * TileSize;
		}
	}
	else if (nextTile.Pos.y * TileSize > position.y)
	{
		position.y += dt * speed;
		if (nextTile.Pos.y * TileSize < position.y)
		{
			position.y = nextTile.Pos.y * TileSize;
		}
	}
	if (nextTile.Pos.x * TileSize == position.x && nextTile.Pos.y * TileSize == position.y)
	{
		pathfinder.pathToEnd.pop_back();
		if (pathfinder.pathToEnd.empty())
		{
			pathfinder.initializedStartandEnd = false;
			pathfinder.found = false;
			if (state == WALK)
				state = WAIT;
			else if (state == WAIT)
				state = LEAVE;
		}
		else
		{
			nextTile = pathfinder.pathToEnd.back();
		}
	}
}