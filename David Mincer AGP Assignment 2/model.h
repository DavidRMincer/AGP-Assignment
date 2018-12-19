#pragma once
#include "objfilemodel.h"

class model
{
private:
	ID3D11Device*			m_pD3DDevice;
	ID3D11DeviceContext*	m_pImmediateContext;

	ObjFileModel*			m_pObject;
	ID3D11VertexShader*		m_pVShader;
	ID3D11PixelShader*		m_pPShader;
	ID3D11InputLayout*		m_pInputLayout;
	ID3D11Buffer*			m_pConstantBuffer;

	float					m_x = 0.0f,
							m_y = 0.0f,
							m_z = 0.0f,
							m_xAngle = 0.0f,
							m_yAngle = 0.0f,
							m_zAngle = 0.0f,
							m_scale = 1.0f;

public:
	model();
	model(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT LoadObjModel(char* filename[255]);
	~model();
};

