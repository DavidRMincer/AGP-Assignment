#pragma once
#include "Moving_Entity.h"
class Fireball :
	public Moving_Entity
{
private:
	int			m_maxDuration,
				m_duration;
	float		m_speed,
				m_xDirection,
				m_yDirection,
				m_zDirection;
	bool		m_active;

public:
	Fireball();
	bool IsActive();
	void SetActive(bool active);
	void Update()
	~Fireball();
};

