#pragma once
#include "Character.h"
#include "Fireball.h"

class Fireball_Manager
{
private:
	vector<Fireball*>	m_vectorofFireballs;
	float					m_speed;

public:
	Fireball_Manager(int size,
		int maxDuration, int damage, float speed);
	void Update();
	void OrganiseVector();
	void Fire(Character* owner);
	~Fireball_Manager();
};

