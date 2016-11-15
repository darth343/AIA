#ifndef SCENE_1_H
#define SCENE_1_H
#include "SceneBase.h"
#include "Camera3.h"
#include "Map.h"
#include "PlayerInfo.h"
#include "GameObject.h"
#include "CharacterData.h"
#include "Train.h"

class Scene1 : public SceneBase
{
public:
	Scene1();
	~Scene1();

	virtual void Init();
	virtual void Update(double dt);
	virtual void Render();
	virtual void Exit();
	virtual void Reset();
	void RenderMap();
	void RenderGO();
	//Update Functions
	void PlayerUpdate(double dt);			// Update to the player 
	void GOupdate(double dt);				// Main GO Collisions
	void MapUpdate(double dt);
	void TrainUpdate(double dt);			// Update train stuff
private:
	vector<GameObject*> m_goList;
	CMap*	m_cMap;							// Handle to the tilemaps
	Vector3 TrainStation, EndPosition;
};

#endif