#include "Enemy.h"



Enemy::Enemy(int maxHealth, int maxMana, float handZ, float range) : Character(maxHealth, maxMana, handZ)
{
	m_range = range;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns true if player in range
//////////////////////////////////////////////////////////////////////////////////////
bool Enemy::TargetInRange(Character * target)
{
	float xDist,
		zDist,
		Distance;

	//Calculate distance
	xDist = m_x - target->GetXPos();
	zDist = m_z - target->GetZPos();

	//TRIGONOMETRY
	Distance = sqrt((xDist * xDist) + (zDist * zDist));

	//Return true if distance < range
	return (Distance <= m_range);
}


Enemy::~Enemy()
{
}
