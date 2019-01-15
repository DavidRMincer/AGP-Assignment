#pragma once
#include "Character.h"
#include <d3d11.h>
#include <math.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>

class camera :
	public Character
{
private:
	bool m_jumping;
	float m_jumpVelocity,
		m_jumpSpeed,
		m_maxPitch = 80.0f;

	void updateDifference();

public:
	camera(float x, float y, float z, float rotation,
		float walkSpeed, float rotationSpeed, float jumpSpeed,
		int maxHealth, int maxMana, float handZ);
	void Up(float distance);
	void Jump();
	void UpdateVelocity(float gravity, float floor);
	void ResetHealth();
	XMMATRIX GetViewMatrix();
	~camera();
};

