#pragma once
#include <d3d11.h>
#include <math.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class camera
{
private:
	bool m_jumping;
	float m_x,
		m_y,
		m_z,
		m_dx,
		m_dy = 0.0f,
		m_dz,
		m_cameraRotation,
		m_jumpVelocity,
		m_walkSpeed,
		m_rotationSpeed,
		m_jumpSpeed;
	XMVECTOR m_position,
		m_lookat,
		m_up;

	void updateDifference();
public:
	camera();
	camera(float x, float y, float z, float rotation,
		float walkSpeed, float rotationSpeed, float jumpSpeed);
	void Rotate(float degrees);
	void Forward(void);
	void Backward(void);
	void StrafeLeft(void);
	void StrafeRight(void);
	void Up(float distance);
	void Jump();
	void UpdateVelocity(float gravity, float floor);
	void Pitch(float degrees);
	XMMATRIX GetViewMatrix();
	~camera();
};

