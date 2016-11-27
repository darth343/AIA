#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H
#include "Vector3.h"
#include "Map.h"
#include <string>
using std::string;

class GameObject
{
public:
	enum GAMEOBJECT_TYPE
	{
		GO_NONE,
		GO_COMMUTER,
		GO_TRAIN,
		GO_BUS,
		GO_TOTAL,
	};

	GameObject(Vector3 scale = Vector3(1, 1, 1));
	~GameObject() {};
	virtual void Update(double dt, CMap* m_cMap = NULL){};
	bool CheckCollision(Vector3 playerPos, Vector3 mapOffset, CMap* m_cMap);
	bool CheckCollision(GameObject* go, CMap* m_cMap = NULL);
	void CollisionResponse();
	bool active;
	int ObjectTileWidth;
	int ObjectTileHeight;
	GAMEOBJECT_TYPE type;
	Vector3 position;
	Vector3 direction;
	Vector3 scale;
};

#endif // !GAMEOBJECT_H
