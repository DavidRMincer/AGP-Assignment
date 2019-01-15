#pragma once
#include "Character.h"
#include "Fireball.h"

class Fireball_Manager
{
private:
	vector<Fireball*>	m_vectorofFireballs;
	int						m_numofActive = 0;
	float					m_speed;

public:
	Fireball_Manager(int size, int maxDuration, int damage,
		float speed, model* fireballModel);
	void Update();
	void OrganiseVector();
	void Fire(Character* owner);
	void Draw(XMMATRIX* view, XMMATRIX* projection);
	void CharacterCollisionCheck(Character* character);
	~Fireball_Manager();
};

