#pragma once
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

class Map
{
private:
	vector<string>		m_map;
	vector<Entity>		m_vectorofRocks;
	vector<Character>	m_vectorofEnemies;

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

public:
	Map(int tileScale, float floor,
		model* rockModel, model* enemyModel);
	void DrawRocks(XMMATRIX* view, XMMATRIX* projection);
	void DrawEnemies(XMMATRIX* view, XMMATRIX* projection);
	void SendtoStart(Entity* entity);
	bool AtEnd(Entity* entity);
	~Map();
};

