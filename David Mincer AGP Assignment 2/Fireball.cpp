#include "Fireball.h"



Fireball::Fireball(int maxDuration, int damage, float speed, model* fireballModel)
{
	m_maxDuration = maxDuration;
	m_damage = damage;
	m_speed = speed;
	m_pModel = fireballModel;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns active state
//////////////////////////////////////////////////////////////////////////////////////
bool Fireball::IsActive()
{
	return m_active;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Sets active state
//////////////////////////////////////////////////////////////////////////////////////
void Fireball::SetActive(bool active)
{
	m_active = active;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns damage
//////////////////////////////////////////////////////////////////////////////////////
int Fireball::GetDamage()
{
	return m_damage;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns true if duration is over 0
//////////////////////////////////////////////////////////////////////////////////////
bool Fireball::IsAlive()
{
	return (m_duration > 0);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Updates position & duration
//////////////////////////////////////////////////////////////////////////////////////
void Fireball::Update()
{
	//Move in direction at speed
	m_x += (m_xDirection * m_speed);
	m_y += (m_yDirection * m_speed);
	m_z += (m_zDirection * m_speed);

	//Subtract 1 from duration
	--m_duration;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Move to character's hand and fire
//////////////////////////////////////////////////////////////////////////////////////
void Fireball::Fire(Character * character)
{
	float magnitude;

	//Set owner
	m_pOwner = character;

	//Move to character's hand
	m_x = m_pOwner->GetXHand();
	m_y = m_pOwner->GetYHand();
	m_z = m_pOwner->GetZHand();

	//Set direction
	m_xDirection = m_x - m_pOwner->GetXPos();
	m_yDirection = m_y - m_pOwner->GetYPos();
	m_zDirection = m_z - m_pOwner->GetZPos();

	//Calculate magnitude
	magnitude = sqrt((m_x * m_x) + (m_y * m_y) + (m_z * m_z));

	//Normalise direction
	m_xDirection /= magnitude;
	m_yDirection /= magnitude;
	m_zDirection /= magnitude;

	//Reset duration
	m_duration = m_maxDuration;

	//Set as active
	m_active = true;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Check collision with character
//////////////////////////////////////////////////////////////////////////////////////
void Fireball::CharacterCollisionCheck(Character * character)
{
	//Ignore if character is the owner
	if (character != m_pOwner)
	{
		float xDist,
			yDist,
			zDist,
			distance,
			radius;

		//Calaculate distance between entities
		xDist = m_x - character->GetXPos();
		yDist = m_y - character->GetYPos();
		zDist = m_z - character->GetZPos();
		distance = sqrt((xDist * xDist) + (yDist * yDist) + (zDist * zDist));

		//Calculate sum of both radii
		radius = m_radius + character->GetRadius();

		//If colliding
		if (distance <= radius)
		{
			//Deal damage to character
			character->AddHealth(-m_damage);

			//Destroy fireball
			m_duration = 0;
		}
	}
}


Fireball::~Fireball()
{
}
