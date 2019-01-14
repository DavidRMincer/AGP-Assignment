#pragma once
#include "Character.h"

class Enemy :
	public Character
{
private:
	float		m_range;

public:
	Enemy(int maxHealth, int maxMana, float handZ, float range);
	bool TargetInRange(Character* target);
	~Enemy();
};

