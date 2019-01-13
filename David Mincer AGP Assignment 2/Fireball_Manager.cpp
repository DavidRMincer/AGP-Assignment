#include "Fireball_Manager.h"



Fireball_Manager::Fireball_Manager(int size, int maxDuration, int damage, float speed, model* fireballModel)
{
	//Creates a 'size' long vector of fireballs
	for (unsigned i = 0; i < size; ++i)
	{
		m_vectorofFireballs.push_back(new Fireball(maxDuration,
			damage,
			speed,
			fireballModel));
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Updates all active fireballs
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::Update()
{
	bool unorganised = false;

	//Update each fireball
	for (auto i : m_vectorofFireballs)
	{
		//Only update if active
		if (i->IsActive())
		{
			//Update position
			i->Update();

			if (!i->IsAlive())
			{
				//Update active state
				i->SetActive(i->IsAlive());

				//Subtract 1 from num of active
				--m_numofActive;

				//Vector is unorganised
				unorganised = true;
			}
		}
	}

	if (unorganised)
		OrganiseVector();
}

//////////////////////////////////////////////////////////////////////////////////////
//	Moves all active fireballs to top of vector
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::OrganiseVector()
{
	bool changed;
	Fireball* temp;

	do
	{
		//Reset changed state
		changed = false;

		for (unsigned i = 0; i < m_vectorofFireballs.size(); ++i)
		{
			//If in range of vector
			if (i + 1 != m_vectorofFireballs.size())
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

			//Add 1 to num of active
			++m_numofActive;
			break;
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//	Draws fireballs in scene
//////////////////////////////////////////////////////////////////////////////////////
void Fireball_Manager::Draw(XMMATRIX * view, XMMATRIX * projection)
{
	//For each fireball
	for (auto i : m_vectorofFireballs)
	{
		//Draw if active
		if (i->IsActive())
			i->Draw(view, projection);
	}
}


Fireball_Manager::~Fireball_Manager()
{
}
