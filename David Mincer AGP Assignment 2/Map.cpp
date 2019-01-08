#include "Map.h"



//////////////////////////////////////////////////////////////////////////////////////
//	Add rock to vector of rocks
//////////////////////////////////////////////////////////////////////////////////////
void Map::AddRock(model * rockModel, float x, float y, float z)
{
	Entity rock;

	rock.AddModel(rockModel);
	rock.SetXPos(x);
	rock.SetYPos(y);
	rock.SetZPos(z);

	m_vectorofRocks.push_back(rock);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Add enemy to vector of enemies
//////////////////////////////////////////////////////////////////////////////////////
void Map::AddEnemy(model * enemyModel, float x, float y, float z)
{
	Character enemy;

	enemy.AddModel(enemyModel);
	enemy.SetXPos(x);
	enemy.SetYPos(y);
	enemy.SetZPos(z);

	m_vectorofEnemies.push_back(enemy);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Loads map
//////////////////////////////////////////////////////////////////////////////////////
Map::Map(int tileScale, float floor, model* rockModel, model* enemyModel)
{
	//Create map layout
	m_map = {	"RRRRR-----------------------------------",
				"RXRR-----------RRRRRRRRRR------------RE-",
				"RRR-R--------------------------------RR-",
				"RR---------RRR---------R----------------",
				"---RR-----------------------------------",
				"------R-R-R-R----------R----------------",
				"-----------------------R----------------",
				"-----------R-RRR-------RR---------------",
				"---------R------------------------------",
				"-----------R------RER---R---------------"
				"-----------RR---------------------------"
				"-----------RRR--------R-R-------------RE"
				"-----------RRRR-R----R----------------RR"
				"---E--------------R-R-----------------RE"
				"----------------R------RRR--------------"
				"--------------R------R------------------"
				"----------------R----R------------------"
				"RR------------R---R--R-------------RRR--"
				"ER--------------R------------------RER--"
				"RR-------------RRR-----------------RRR--"
				"-------------------R--------------------"
				"---------------------R------------------"
				"-------------------R-R------------------"
				"RR-----------------R--------------------"
				"RR----R---R---R-R-R------------------E--"
				"---RR---R---R---------------------------"
				"-----------------RR-----R---------------"
				"---------------RRSR-RRR---R-RR----------" };

	m_tileScale = tileScale;
	m_width = m_map[0].length();
	m_length = m_map.size();

	//Set points
	for (int x = 0; x < m_width; ++x)
	{
		for (int z = 0; z < m_length; ++z)
		{
			switch (m_map[z][x])
			{
			//Set start point
			case 'S':
				AddRock(rockModel, x, floor + m_tileScale, z);

				m_xStart = x;
				m_yStart = floor + (m_tileScale * 2);
				m_zStart = z;
				break;
			//Set end point
			case 'X':
				AddRock(rockModel, x, floor + m_tileScale, z);

				m_xEnd = x;
				m_zEnd = z;
				break;
			//Add enemy
			case 'E':
				AddRock(rockModel, x, floor + m_tileScale, z);
				AddEnemy(enemyModel, x, floor + (m_tileScale * 2), z);
				break;
			//Add rock
			case 'R':
				AddRock(rockModel, x, floor + m_tileScale, z);
				break;
			default:
				break;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Draws all rocks in the scene
//////////////////////////////////////////////////////////////////////////////////////
void Map::DrawRocks(XMMATRIX * view, XMMATRIX * projection)
{
	//Draw each rock
	for (auto index : m_vectorofRocks)
	{
		index.GetModel()->Draw(view, projection);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Draws all enemies in the scene
//////////////////////////////////////////////////////////////////////////////////////
void Map::DrawEnemies(XMMATRIX * view, XMMATRIX * projection)
{
	//Draw each enemy
	for (auto index : m_vectorofEnemies)
	{
		index.GetModel()->Draw(view, projection);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Sets entity position as start point
//////////////////////////////////////////////////////////////////////////////////////
void Map::SendtoStart(Entity * entity)
{
	entity->SetXPos(m_xStart);
	entity->SetYPos(m_yStart);
	entity->SetZPos(m_zStart);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns true if end reached
//////////////////////////////////////////////////////////////////////////////////////
bool Map::AtEnd(Entity * entity)
{
	float distance,
		xDist,
		zDist;

	xDist = m_xEnd - entity->GetXPos();
	zDist = m_zEnd - entity->GetZPos();

	distance = sqrt((xDist * xDist) +
		(zDist * zDist));

	return (distance <= m_tileScale);
}


Map::~Map()
{
}
