#pragma once
#include "Character.h"

class Fireball_Manager
{
private:
	vector<Moving_Entity*>	m_vecotrofFireballs;
	float					m_speed;

public:
	Fireball_Manager();
	~Fireball_Manager();
};

