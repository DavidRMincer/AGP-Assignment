#include "camera.h"



void camera::updateDifference()
{
	m_dx = sin(m_rotation * (XM_PI / 180));
	m_dz = cos(m_rotation * (XM_PI / 180));
}

camera::camera(float x, float y, float z, float rotation,
	float walkSpeed, float rotationSpeed, float jumpSpeed,
	int maxHealth, int maxMana, float handZ) : Character(maxHealth, maxMana, handZ)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_yAngle = rotation;

	updateDifference();

	m_walkSpeed = walkSpeed;
	m_jumpSpeed = jumpSpeed;
}

void camera::Up(float distance)
{
	m_y += distance;
}

//////////////////////////////////////////////////////////////////////////////////////
//Initialise jump
//////////////////////////////////////////////////////////////////////////////////////
void camera::Jump()
{
	if (!m_jumping)
	{
		m_jumpVelocity = m_jumpSpeed;
		m_jumping = true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////
//Updates velocity
//////////////////////////////////////////////////////////////////////////////////////
void camera::UpdateVelocity(float gravity, float floor)
{
	if (m_y > floor) m_jumpVelocity -= gravity;
	else if (m_jumpVelocity < 0.0f)
	{
		m_jumpVelocity = 0.0f;
		m_jumping = false;
	}
	m_y += m_jumpVelocity;
}

XMMATRIX camera::GetViewMatrix()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y + m_dy, m_z + m_dz, 0.0f);

	XMMATRIX viewMat = XMMatrixLookAtLH(m_position, m_lookat, m_up);

	return viewMat;
}


camera::~camera()
{
}
