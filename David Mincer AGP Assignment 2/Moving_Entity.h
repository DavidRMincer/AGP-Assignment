#pragma once
#include "Entity.h"
class Moving_Entity :
	public Entity
{
protected:
	float	m_rotation,
			m_walkSpeed,
			m_rotationSpeed = 0.001f;

public:
	Moving_Entity(ID3D11Device* device, ID3D11DeviceContext* context);
	void Forward(void);
	void Backward(void);
	void StrafeLeft(void);
	void StrafeRight(void);
	void LookAt(Entity* target);
	~Moving_Entity();
};

