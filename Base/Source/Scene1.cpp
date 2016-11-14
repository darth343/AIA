#include "Scene1.h"
#include "GL\glew.h"

#include "shader.hpp"
#include "MeshBuilder.h"
#include "Application.h"
#include "Utility.h"
#include "LoadTGA.h"
#include <sstream>
#include "SpriteAnimation.h"

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
	GameObject* commuter1 = new GameObject();
	commuter1->active = true;
	commuter1->type = GameObject::GO_COMMUTER;
	commuter1->scale = m_cMap->GetTileSize();
	commuter1->position.Set(0, 0, 0);
	commuter1->ObjectTileHeight = 2;
	commuter1->ObjectTileWidth = 6;
	m_goList.push_back(commuter1);
}

void Scene1::PlayerUpdate(double dt)
{
}

void Scene1::GOupdate(double dt)
{
}

void Scene1::MapUpdate(double dt)
{
}

void Scene1::Update(double dt)
{
	SceneBase::Update(dt);
	fps = (float)(1.f / dt);

	for (int i = 0; i < m_goList.size(); ++i)
	{

	}
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
					Render2DMesh(meshList[GEO_COMMUTER], false, m_cMap->GetTileSize() * 0.5, m_goList[i]->position.x + (j * m_cMap->GetTileSize() * 0.5), m_goList[i]->position.y + (k * m_cMap->GetTileSize() * 0.5), false);
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
	//RenderGO();
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