#include "camera.h"



void camera::updateDifference()
{
	m_dx = sin(m_cameraRotation * (XM_PI / 180));
	m_dz = cos(m_cameraRotation * (XM_PI / 180));
}

camera::camera()
{
}

camera::camera(float x, float y, float z, float rotation)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_cameraRotation = rotation;

	updateDifference();
}

float camera::getMoveSpeed(void)
{
	return m_moveSpeed;
}

float camera::getRotateSpeed(void)
{
	return m_rotateSpeed;
}

float camera::getJumpSpeed(void)
{
	return m_jumpSpeed;
}

void camera::Rotate(float degrees)
{
	m_cameraRotation += degrees;
	updateDifference();
}

void camera::Forward(float distance)
{
	m_x += distance * m_dx;
	m_z += distance * m_dz;
}

void camera::Strafe(float distance)
{
	XMVECTOR forward = (m_lookat - m_position),
		direction = XMVector3Cross(m_up, forward);
	
	m_x += direction.x * distance;
	m_z += direction.z * distance;
}

void camera::Up(float distance)
{
	m_y += distance;
}

void camera::Jump(void)
{
	m_jumpVelocity = m_jumpSpeed;
	m_jumping = true;
}

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

void camera::Pitch(float degrees)
{
	m_dy += sin(XMConvertToRadians(degrees));

	if (XMConvertToDegrees(m_dy) > 80.0f) m_dy = XMConvertToRadians(80.0f);
	else if (XMConvertToDegrees(m_dy) < -80.0f) m_dy = XMConvertToRadians(-80.0f);
}

bool camera::isJumping(void)
{
	return m_jumping;
}

XMMATRIX camera::GetViewMatrix()
{
	m_position = XMVectorSet(m_x, m_y, m_z, 0.0f);
	m_lookat = XMVectorSet(m_x + m_dx, m_y + m_dy, m_z + m_dz, 0.0f);
	m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);

	XMMATRIX viewMat = XMMatrixLookAtLH(m_position, m_lookat, m_up);

	return viewMat;
}


camera::~camera()
{
}
