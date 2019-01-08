#include "Entity.h"



Entity::Entity()
{
}

void Entity::AddModel(model * model)
{
	m_pModel = model;
}

void Entity::SetXPos(float x)
{
	m_x = x;

	if (m_pModel) m_pModel->SetXPos(x);
}

void Entity::SetYPos(float y)
{
	m_y = y;

	if (m_pModel) m_pModel->SetYPos(y);
}

void Entity::SetZPos(float z)
{
	m_z = z;

	if (m_pModel) m_pModel->SetZPos(z);
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

	if (m_pModel) m_pModel->AddXPos(x);
}

void Entity::MoveYPos(float y)
{
	m_y += y;

	if (m_pModel) m_pModel->AddYPos(y);
}

void Entity::MoveZPos(float z)
{
	m_z += z;

	if (m_pModel) m_pModel->AddZPos(z);
}

void Entity::Pitch(float degrees)
{
	m_xAngle += degrees;

	m_dy = sin(XMConvertToRadians(m_xAngle));

	if (XMConvertToDegrees(m_dy) > m_maxPitch) m_dy = XMConvertToRadians(m_maxPitch);
	else if (XMConvertToDegrees(m_dy) < -m_maxPitch) m_dy = XMConvertToRadians(-m_maxPitch);
	
	if (m_pModel) m_pModel->SetXAngle(m_dy);
}

void Entity::Yaw(float degrees)
{
	m_yAngle += degrees;

	m_dx = sin(m_yAngle * (XM_PI / 180));
	m_dz = cos(m_yAngle * (XM_PI / 180));

	if (m_pModel) m_pModel->SetYAngle(m_yAngle);
}

Entity::~Entity()
{
}
