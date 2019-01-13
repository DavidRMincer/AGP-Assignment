#pragma once
#include "Character.h"
class Fireball :
	public Moving_Entity
{
private:
	int			m_maxDuration,
				m_duration,
				m_damage;
	float		m_speed,
				m_xDirection,
				m_yDirection,
				m_zDirection;
	bool		m_active = false;

	Character	*m_pOwner;

public:
	Fireball(int maxDuration, int damage, float speed,
		model* fireballModel);
	bool IsActive();
	void SetActive(bool active);
	int GetDamage();
	bool IsAlive();
	void Update();
	void Fire(Character* character);
	~Fireball();
};

