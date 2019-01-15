#pragma once
#include "Moving_Entity.h"
class Character :
	public Moving_Entity
{
protected:
	int			m_health,
				m_mana,
				m_maxHealth,
				m_maxMana;
	
	float		m_xHand = 0.0f,
				m_yHand = 0.0f,
				m_zHand;

public:
	Character(int maxHealth, int maxMana, float handZ);
	bool ReadytoFire();
	bool IsAlive();

	//////////////////////////////////////////////////////////////////////////////////////
	//	Gets values
	//////////////////////////////////////////////////////////////////////////////////////
	int GetHealth();
	int GetMana();
	float GetXHand();
	float GetYHand();
	float GetZHand();

	//////////////////////////////////////////////////////////////////////////////////////
	//	Adds to values
	//////////////////////////////////////////////////////////////////////////////////////
	void AddHealth(int health);
	void AddMana(int mana);
	void RechargeMana();

	~Character();
};

