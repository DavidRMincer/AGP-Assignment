#include "Moving_Entity.h"



void Moving_Entity::updateDifference()
{
	m_dx = sin(m_rotation * (XM_PI / 180));
	m_dz = cos(m_rotation * (XM_PI / 180));
}

Moving_Entity::Moving_Entity()
{
}

void Moving_Entity::Forward(void)
{
	m_x += m_walkSpeed * m_dx;
	m_z += m_walkSpeed * m_dz;
}

void Moving_Entity::Backward(void)
{
	m_x += -m_walkSpeed * m_dx;
	m_z += -m_walkSpeed * m_dz;
}

void Moving_Entity::StrafeLeft(void)
{
	XMVECTOR forward = (m_lookat - m_position),
		direction = XMVector3Cross(m_up, forward);

	m_x += direction.x * -m_walkSpeed;
	m_z += direction.z * -m_walkSpeed;
}

void Moving_Entity::StrafeRight(void)
{
	XMVECTOR forward = (m_lookat - m_position),
		direction = XMVector3Cross(m_up, forward);

	m_x += direction.x * m_walkSpeed;
	m_z += direction.z * m_walkSpeed;
}


Moving_Entity::~Moving_Entity()
{
}
