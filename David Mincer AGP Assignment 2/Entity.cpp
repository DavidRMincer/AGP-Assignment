#include "Entity.h"



Entity::Entity()
{
}

void Entity::SetXPos(float x)
{
	m_x = x;
}

void Entity::SetYPos(float y)
{
	m_y = y;
}

void Entity::SetZPos(float z)
{
	m_z = z;
}


float Entity::GetXPos(void)
{
	return m_x;
}

float Entity::GetYPos(void)
{
	return m_y;
}

float Entity::GetZPos(void)
{
	return m_z;
}

model * Entity::GetModel(void)
{
	return m_pModel;
}

void Entity::MoveXPos(float x)
{
	m_x += x;
}

void Entity::MoveYPos(float y)
{
	m_y += y;
}

void Entity::MoveZPos(float z)
{
	m_z += z;
}

Entity::~Entity()
{
}
