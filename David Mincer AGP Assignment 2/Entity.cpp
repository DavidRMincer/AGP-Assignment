#include "Entity.h"



Entity::Entity()
{
}

void Entity::AddModel(model * model)
{
	m_pModel = model;
}

void Entity::Draw(XMMATRIX * view, XMMATRIX * projection)
{
	if (m_pModel)
	{
		//Rotate
		m_pModel->SetXAngle(m_xAngle);
		m_pModel->SetYAngle(m_yAngle);
		m_pModel->SetZAngle(m_zAngle);

		//Translate
		m_pModel->SetXPos(m_x);
		m_pModel->SetYPos(m_y);
		m_pModel->SetZPos(m_z);

		//Draw
		m_pModel->Draw(view, projection);
	}
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

void Entity::Pitch(float degrees)
{
	m_xAngle += degrees;

	m_dy = sin(XMConvertToRadians(m_xAngle));

	if (XMConvertToDegrees(m_dy) > m_maxPitch) m_dy = XMConvertToRadians(m_maxPitch);
	else if (XMConvertToDegrees(m_dy) < -m_maxPitch) m_dy = XMConvertToRadians(-m_maxPitch);
}

void Entity::Yaw(float degrees)
{
	m_yAngle += degrees;

	m_dx = sin(m_yAngle * (XM_PI / 180));
	m_dz = cos(m_yAngle * (XM_PI / 180));
}

Entity::~Entity()
{
}
