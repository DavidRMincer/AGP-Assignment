#pragma once
#include "Moving_Entity.h"
#include <d3d11.h>
#include <math.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class camera :
	public Moving_Entity
{
private:
	bool m_jumping;
	float m_jumpVelocity,
		m_jumpSpeed,
		m_maxPitch = 75.0f;

	void updateDifference();

public:
	camera(float x, float y, float z, float rotation,
		float walkSpeed, float rotationSpeed, float jumpSpeed);
	void Up(float distance);
	void Jump();
	void UpdateVelocity(float gravity, float floor);
	XMMATRIX GetViewMatrix();
	~camera();
};

