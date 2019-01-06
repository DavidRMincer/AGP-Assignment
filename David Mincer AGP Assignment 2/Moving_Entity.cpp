#include "Moving_Entity.h"



Moving_Entity::Moving_Entity(ID3D11Device * device, ID3D11DeviceContext * context) : Entity (device, context)
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

void Moving_Entity::LookAt(Entity * target)
{
	float xDist,
		zDist,
		magnitude,
		modelMagnitude,
		angle;

	//Get distance from target
	xDist = target->GetXPos() - m_x;
	zDist = target->GetZPos() - m_z;

	//Set angle
	angle = atan2(xDist, zDist) * m_rotationSpeed;

	//Rotate
	Yaw(angle);
}


Moving_Entity::~Moving_Entity()
{
}
