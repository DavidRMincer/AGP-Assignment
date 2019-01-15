#pragma once
#include <vector>
#include <string>
#include "Enemy.h"

using namespace std;

class Map
{
private:
	vector<string>		m_map;
	vector<Entity>		m_vectorofRocks;
	vector<Enemy*>		m_vectorofEnemies;

	model				*m_pEndModel,
						*m_pLavaModel;

	int					m_tileScale,
						m_width,
						m_length;
	float				m_xStart,
						m_yStart,
						m_zStart,
						m_xEnd,
						m_zEnd;

	void AddRock(model* rockModel, float x, float y, float z);
	void AddEnemy(model* enemyModel, float x, float y, float z);
	void AddEnd(model* endModel, float y);

public:
	Map(int tileScale, float floor,
		model* rockModel, model* enemyModel, model* endModel,
		model* lavaModel);
	void UpdateEnemies(Entity* player);
	void DrawLevel(XMMATRIX* view, XMMATRIX* projection);
	void SendtoStart(Entity* entity);
	bool AtEnd(Entity* entity);
	float GetWidth();
	float GetLength();
	bool CharacterToRockCollision(Character* character);
	vector<Enemy*> GetVectorofEnemies();
	~Map();
};

