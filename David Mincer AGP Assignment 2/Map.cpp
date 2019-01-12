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
	Character enemy(10, 10, 1);

	enemy.AddModel(enemyModel);
	enemy.SetXPos(x);
	enemy.SetYPos(y);
	enemy.SetZPos(z);

	m_vectorofEnemies.push_back(enemy);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set end point model
//////////////////////////////////////////////////////////////////////////////////////
void Map::AddEnd(model * endModel, float y)
{
	m_pEndModel = endModel;

	m_pEndModel->SetXPos(m_xEnd);
	m_pEndModel->SetYPos(y);
	m_pEndModel->SetZPos(m_zEnd);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Loads map
//////////////////////////////////////////////////////////////////////////////////////
Map::Map(int tileScale, float floor, model* rockModel, model* enemyModel, model* endModel)
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
				"-----------R------RER---R---------------",
				"-----------RR---------------------------",
				"-----------RRR--------R-R-------------RE",
				"-----------RRRR-R----R----------------RR",
				"---E--------------R-R-----------------RE",
				"----------------R------RRR--------------",
				"--------------R------R------------------",
				"----------------R----R------------------",
				"RR------------R---R--R-------------RRR--",
				"ER--------------R------------------RER--",
				"RR-------------RRR-----------------RRR--",
				"-------------------R--------------------",
				"---------------------R------------------",
				"-------------------R-R------------------",
				"RR-----------------R--------------------",
				"RR----R---R---R-R-R------------------E--",
				"---RR---R---R---------------------------",
				"-----------------RR-----R---------------",
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
				AddRock(
					rockModel,
					x * m_tileScale,
					floor + m_tileScale,
					z * m_tileScale);

				m_xStart = x * m_tileScale;
				m_yStart = floor + (m_tileScale * 2);
				m_zStart = z * m_tileScale;
				break;
			//Set end point
			case 'X':
				AddRock(
					rockModel,
					x * m_tileScale,
					floor + m_tileScale,
					z * m_tileScale);

				m_xEnd = x * m_tileScale;
				m_zEnd = z * m_tileScale;

				AddEnd(endModel, floor + (m_tileScale * 2));
				break;
			//Add enemy
			case 'E':
				AddRock(
					rockModel,
					x * m_tileScale,
					floor + m_tileScale,
					z * m_tileScale);
				AddEnemy(
					enemyModel,
					x * m_tileScale,
					floor + (m_tileScale * 2),
					z * m_tileScale);
				break;
			//Add rock
			case 'R':
				AddRock(
					rockModel,
					x * m_tileScale,
					floor + m_tileScale,
					z * m_tileScale);
				break;
			default:
				break;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Updates enemies in the scene
//////////////////////////////////////////////////////////////////////////////////////
void Map::UpdateEnemies(Entity * player)
{
	//Update each enemy
	for (auto index : m_vectorofEnemies)
	{
		index.LookAt(player);
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Draws all objects in scene
//////////////////////////////////////////////////////////////////////////////////////
void Map::DrawLevel(XMMATRIX * view, XMMATRIX * projection)
{
	//Draw each rock
	for (auto index : m_vectorofRocks)
	{
		index.Draw(view, projection);
	}

	//Draw each enemy
	for (auto index : m_vectorofEnemies)
	{
		index.Draw(view, projection);
	}

	m_pEndModel->Draw(view, projection);
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

//////////////////////////////////////////////////////////////////////////////////////
//	Returns width of level
//////////////////////////////////////////////////////////////////////////////////////
float Map::GetWidth()
{
	return m_width * m_tileScale;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns true if end reached
//////////////////////////////////////////////////////////////////////////////////////
float Map::GetLength()
{
	return m_length * m_tileScale;
}


Map::~Map()
{
}