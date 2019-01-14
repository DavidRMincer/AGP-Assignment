#include "Character.h"



Character::Character(int maxHealth, int maxMana, float handZ)
{
	m_maxHealth = maxHealth;
	m_health = m_maxHealth;

	m_maxMana = maxMana;
	m_mana = m_maxMana;

	
	m_zHand = handZ;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns true if mana fully charged
//////////////////////////////////////////////////////////////////////////////////////
bool Character::ReadytoFire()
{
	return (m_mana == m_maxMana);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns health
//////////////////////////////////////////////////////////////////////////////////////
int Character::GetHealth()
{
	return m_health;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns mana
//////////////////////////////////////////////////////////////////////////////////////
int Character::GetMana()
{
	return m_mana;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns hand x position
//////////////////////////////////////////////////////////////////////////////////////
float Character::GetXHand()
{
	float x;

	//Rotate
	x = sin(m_yAngle * (XM_PI / 180));
	//Translate
	x += m_xHand + m_x;

	//Return result
	return x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns hand y position
//////////////////////////////////////////////////////////////////////////////////////
float Character::GetYHand()
{
	float y;

	//Rotate
	y = sin(m_xAngle * (XM_PI / 180));
	//Translate
	y += m_y;

	//Return result
	return y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns hand z position
//////////////////////////////////////////////////////////////////////////////////////
float Character::GetZHand()
{
	float z;

	//Rotate
	z = m_zHand * cos(m_yAngle * (XM_PI / 180));
	z *= cos(m_xAngle * (XM_PI / 180));
	//Translate
	z += m_z;

	//Return result
	return z;
}


//////////////////////////////////////////////////////////////////////////////////////
//	Adds health to current health
//////////////////////////////////////////////////////////////////////////////////////
void Character::AddHealth(int health)
{
	//Add health
	m_health += health;

	//Constrain health between 0 and max
	if (m_health > m_maxHealth)
		m_health = m_maxHealth;
	else if (m_health < 0)
		m_health = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds mana to current mana
//////////////////////////////////////////////////////////////////////////////////////
void Character::AddMana(int mana)
{
	//Add mana
	m_mana += mana;

	//Constrain mana between 0 and max
	if (m_mana > m_maxMana)
		m_mana = m_maxMana;
	else if (m_mana < 0)
		m_mana = 0;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds 1 to mana
//////////////////////////////////////////////////////////////////////////////////////
void Character::RechargeMana()
{
	//Add mana
	++m_mana;

	//Constrain mana between 0 and max
	if (m_mana > m_maxMana)
		m_mana = m_maxMana;
	else if (m_mana < 0)
		m_mana = 0;
}

Character::~Character()
{
}
