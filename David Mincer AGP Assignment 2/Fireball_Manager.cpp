#include "Fireball_Manager.h"



Fireball_Manager::Fireball_Manager(int size, int maxDuration, int damage, float speed)
{
	//Creates a 'size' long vector of fireballs
	for (unsigned i = 0; i < size; ++i)
	{
		m_vectorofFireballs.push_back(new Fireball(maxDuration,
			damage,
			speed));
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Updates all active fireballs
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::Update()
{
	//Update each fireball
	for (auto i : m_vectorofFireballs)
	{
		//Only update if active
		if (i->IsActive())
			i->Update();
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Moves all active fireballs to top of vector
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::OrganiseVector()
{
	bool changed = false;
	Fireball* temp;

	do
	{
		for (unsigned i = 0; i < m_vectorofFireballs.size(); ++i)
		{
			//If 2 fireballs are in the wrong order
			if (!m_vectorofFireballs[i]->IsActive() &&
				m_vectorofFireballs[i + 1]->IsActive())
			{
				//Swap i and i+1
				temp = m_vectorofFireballs[i + 1];
				m_vectorofFireballs[i + 1] = m_vectorofFireballs[i];
				m_vectorofFireballs[i] = temp;

				//Set changed to true
				changed = true;
			}
		}
	} while (changed);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Fires next inactive fireball
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::Fire(Character * owner)
{
	//Check each fireball
	for (unsigned i = 0; i < m_vectorofFireballs.size(); ++i)
	{
		//If the current fireball is not active
		if (!m_vectorofFireballs[i]->IsActive())
		{
			//Fire fireball
			m_vectorofFireballs[i]->Fire(owner);
			break;
		}
	}
}


Fireball_Manager::~Fireball_Manager()
{
}
