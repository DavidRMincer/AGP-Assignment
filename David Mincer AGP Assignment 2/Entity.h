#pragma once
#include <d3d11.h>
#include <math.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>
#include "model.h"

class Entity
{
protected:
	float		m_x = 0.0f,
				m_y = 0.0f,
				m_z = 0.0f,
				m_dx = 0.0f,
				m_dy = 0.0f,
				m_dz = 0.0f;
	XMVECTOR	m_position,
				m_lookat,
				m_up = XMVectorSet(0.0f, 1.0f, 0.0f, 0.0f);
	model		*m_pModel;
public:
	Entity();

	//////////////////////////////////////////////////////////////////////////////////////
	//	Sets values
	//////////////////////////////////////////////////////////////////////////////////////
	void SetXPos(float x);
	void SetYPos(float y);
	void SetZPos(float z);

	//////////////////////////////////////////////////////////////////////////////////////
	//	Gets values
	//////////////////////////////////////////////////////////////////////////////////////
	float GetXPos(void);
	float GetYPos(void);
	float GetZPos(void);
	model* GetModel(void);

	//////////////////////////////////////////////////////////////////////////////////////
	//	Increments values
	//////////////////////////////////////////////////////////////////////////////////////
	void MoveXPos(float x);
	void MoveYPos(float y);
	void MoveZPos(float z);
	void XRotate(float x);
	void YRotate(float y);
	void ZRotate(float z);
	~Entity();
};

