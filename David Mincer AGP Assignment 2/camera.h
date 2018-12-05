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
		m_jumpVelocity;
	XMVECTOR m_position,
		m_lookat,
		m_up;

	void updateDifference();
public:
	camera();
	camera(float x, float y, float z, float rotation);
	void Rotate(float degrees);
	void Forward(float distance);
	void Strafe(float distance);
	void Up(float distance);
	void Jump(float force);
	void UpdateVelocity(float gravity, float floor);
	void Pitch(float degrees);
	bool isJumping(void);
	XMMATRIX GetViewMatrix();
	~camera();
};

