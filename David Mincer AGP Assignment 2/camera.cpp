#include "camera.h"



void camera::updateDifference()
{
	m_dx = sin(m_cameraRotation * (XM_PI / 180));
	m_dz = cos(m_cameraRotation * (XM_PI / 180));
}

camera::camera()
{
}

camera::camera(float x, float y, float z, float rotation,
	float walkSpeed, float rotationSpeed, float jumpSpeed)
{
	m_x = x;
	m_y = y;
	m_z = z;
	m_cameraRotation = rotation;

	updateDifference();

	m_walkSpeed = walkSpeed;
	m_rotationSpeed = rotationSpeed;
	m_jumpSpeed = jumpSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////
//Rotates camera on y axis
//////////////////////////////////////////////////////////////////////////////////////
void camera::Rotate(float degrees)
{
	m_cameraRotation += (degrees * m_rotationSpeed);
	updateDifference();
}

//////////////////////////////////////////////////////////////////////////////////////
//Move camera forward
//////////////////////////////////////////////////////////////////////////////////////
void camera::Forward(void)
{
	m_x += m_walkSpeed * m_dx;
	m_z += m_walkSpeed * m_dz;
}

//////////////////////////////////////////////////////////////////////////////////////
//Move camera backward
//////////////////////////////////////////////////////////////////////////////////////
void camera::Backward(void)
{
	m_x += -m_walkSpeed * m_dx;
	m_z += -m_walkSpeed * m_dz;
}

//////////////////////////////////////////////////////////////////////////////////////
//Move camera left
//////////////////////////////////////////////////////////////////////////////////////
void camera::StrafeLeft(void)
{
	XMVECTOR forward = (m_lookat - m_position),
		direction = XMVector3Cross(m_up, forward);
	
	m_x += direction.x * -m_walkSpeed;
	m_z += direction.z * -m_walkSpeed;
}

//////////////////////////////////////////////////////////////////////////////////////
//Move camera right
//////////////////////////////////////////////////////////////////////////////////////
void camera::StrafeRight(void)
{
	XMVECTOR forward = (m_lookat - m_position),
		direction = XMVector3Cross(m_up, forward);

	m_x += direction.x * m_walkSpeed;
	m_z += direction.z * m_walkSpeed;
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

//////////////////////////////////////////////////////////////////////////////////////
//Rotates camera on x axis
//////////////////////////////////////////////////////////////////////////////////////
void camera::Pitch(float degrees)
{
	m_dy += sin(XMConvertToRadians(degrees * m_rotationSpeed));

	if (XMConvertToDegrees(m_dy) > 80.0f) m_dy = XMConvertToRadians(80.0f);
	else if (XMConvertToDegrees(m_dy) < -80.0f) m_dy = XMConvertToRadians(-80.0f);
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
