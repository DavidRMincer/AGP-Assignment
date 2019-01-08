#pragma once
#include "Moving_Entity.h"
class Character :
	public Moving_Entity
{
protected:
	int			m_health,
				m_mana;
	const int	m_maxHealth = 100,
				m_maxMana = 10;
	
	float		m_xHand,
				m_yHand,
				m_zHand;

public:
	Character();
	~Character();
};

