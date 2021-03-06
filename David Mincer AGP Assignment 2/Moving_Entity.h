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
	Moving_Entity();
	void Forward(void);
	void Backward(void);
	void StrafeLeft(void);
	void StrafeRight(void);
	void LookAt(Entity* target);
	~Moving_Entity();
};

