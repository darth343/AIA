#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "SpriteAnimation.h"
#include "Commuter.h"

Scene1::Scene1()
: m_cMap(NULL)
{
}

Scene1::~Scene1()
{
	if (m_cMap)
	{
		delete m_cMap;
		m_cMap = NULL;
	}
}

void Scene1::Reset()
{
}

void Scene1::Init()
{
	SceneBase::Init();

	// Initialise and load the tile map
	m_cMap = new CMap();
	m_cMap->Init(Application::GetInstance().GetScreenHeight(), Application::GetInstance().GetScreenWidth(), 24);
	m_cMap->LoadMap("Data//testMap.csv");
	//std::cout << m_cMap->GetNumOfTiles_Height() << m_cMap->GetNumOfTiles_Width() << std::endl;

	// Commuters

	for (int i = 0; i < 10; i++)
	{
		Commuter* commuter1 = new Commuter();
		commuter1->active = true;
		commuter1->type = GameObject::GO_COMMUTER;
		commuter1->scale = m_cMap->GetTileSize();
		Vector3 randomCommuterPos(Math::RandIntMinMax(0, m_cMap->GetNumOfTiles_Width() - 1), Math::RandIntMinMax(0, m_cMap->GetNumOfTiles_Height() - 1), 0);
		while (m_cMap->theMap[randomCommuterPos.y][randomCommuterPos.x].BlockID != 33)
		{
			randomCommuterPos.Set(Math::RandIntMinMax(0, m_cMap->GetNumOfTiles_Width()-1), Math::RandIntMinMax(0, m_cMap->GetNumOfTiles_Height() - 1), 0);
		}
		std::cout << m_cMap->theMap[randomCommuterPos.y][randomCommuterPos.x].BlockID << " " << randomCommuterPos << std::endl;
		commuter1->position.Set(randomCommuterPos.x * m_cMap->GetTileSize(), randomCommuterPos.y * m_cMap->GetTileSize(), 0);
		//commuter1->position.Set(1 * m_cMap->GetTileSize(), 1 * m_cMap->GetTileSize(), 0);
		m_goList.push_back(commuter1);
	}


	// Train
	m_Train = new Train;
	m_Train->type = GameObject::GO_TRAIN;
	m_Train->active = true;
	m_Train->scale = m_cMap->GetTileSize();
	m_Train->position.Set(27, 547, 0);
	m_Train->ObjectTileHeight = 2.5;
	m_Train->ObjectTileWidth = 8;
	m_goList.push_back(m_Train);

	TrainStation.Set(27, 547, 0);
	EndPosition.Set(675, 547, 0);
}

void Scene1::TrainUpdate(double dt)
{
	Train1.TrainUpdate(dt);

	// Check if train in Move state
	if (Train1.getTrainState() == 3)
	{
		// Check if train pos is TO state
		if (Train1.getTrainPosState() == 0)
		{
			// If the Train x is smaller than the End x
			if (m_Train->position.x < EndPosition.x)
			{
				m_Train->MoveTO(dt);
			}
			// When the Train reach the end, change the train pos state to FROM state
			else
			{
				Train1.setTrainPosState(1);
			}
		}

		// Check if train pos is FROM state
		if (Train1.getTrainPosState() == 1)
		{
			// If the Train x is bigger than the Station x
			if (m_Train->position.x > TrainStation.x)
			{
				m_Train->MoveFROM(dt);
			}
			// When the Train reach back to the station, change the train pos state to NONE
			else
			{
				Train1.setTrainPosState(2);
			}
		}
		
	}
	else // When train change to Stop state
	{
		// Set the trainPos state to NONE state
		Train1.setTrainPosState(2);
	}
}

void Scene1::PlayerUpdate(double dt)
{
}

void Scene1::GOupdate(double dt)
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		if (m_goList[i]->type == GameObject::GO_COMMUTER)
		{
			Commuter* temp = dynamic_cast<Commuter*>(m_goList[i]);
			temp->Update(dt, m_cMap);
		}
	}
}

void Scene1::MapUpdate(double dt)
{
}

void Scene1::Update(double dt)
{
	SceneBase::Update(dt);
	TrainUpdate(dt);

	fps = (float)(1.f / dt);
	GOupdate(dt);
}

void Scene1::RenderMap()
{
	static float xpos = 0.f;
	static float ypos = 0.f;

	if (Application::IsKeyPressed('U'))
	{
		ypos += 0.5f;
	}
	if (Application::IsKeyPressed('J'))
	{
		ypos -= 0.5f;
	}
	if (Application::IsKeyPressed('H'))
	{
		xpos -= 0.5f;
	}
	if (Application::IsKeyPressed('K'))
	{
		xpos += 0.5f;
	}

	//RenderBackground(meshList[GEO_BACKGROUND]);
	RenderTileMap(meshList[GEO_TILESET1], m_cMap);
	std::ostringstream ss;
	//On screen text
	ss.str("");
	ss.precision(5);
	ss << "FPS: " << fps;
	//RenderTextOnScreen(meshList[GEO_TEXT], ss.str(), Color(1, 1, 0), 30, 0, 0);
}

void Scene1::RenderGO()
{
	for (int i = 0; i < m_goList.size(); i++)
	{
		switch (m_goList[i]->type)
		{
		case GameObject::GO_COMMUTER:
			for (int j = 0; j < m_goList[i]->ObjectTileWidth; j++)
			{
				for (int k = 0; k < m_goList[i]->ObjectTileHeight; k++)
				{
					Render2DMesh(meshList[GEO_COMMUTER], false, m_cMap->GetTileSize(), m_goList[i]->position.x + (j * m_cMap->GetTileSize() * 0.5), m_goList[i]->position.y + (k * m_cMap->GetTileSize() * 0.5), false);
				}
			}
			break;
		case GameObject::GO_TRAIN:
			for (int j = 0; j < m_goList[i]->ObjectTileWidth; j++)
			{
				for (int k = 0; k < m_goList[i]->ObjectTileHeight; k++)
				{
					Render2DMesh(meshList[GEO_TRAIN], false, m_cMap->GetTileSize(), m_goList[i]->position.x + (j * m_cMap->GetTileSize() * 0.5), m_goList[i]->position.y + (k * m_cMap->GetTileSize() * 0.5), false);
				}
			}
			break;
		}
	}
}

void Scene1::Render()
{
	SceneBase::Render();
	RenderMap();
	RenderGO();
}

void Scene1::Exit()
{
	// Cleanup VBO
	for(int i = 0; i < NUM_GEOMETRY; ++i)
	{
		if(meshList[i])
			delete meshList[i];
	}
	glDeleteProgram(m_programID);
	glDeleteVertexArrays(1, &m_vertexArrayID);
}