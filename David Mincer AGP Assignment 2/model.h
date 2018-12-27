#pragma once
#include "objfilemodel.h"

struct MODEL_CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;		// 64 bytes
	XMVECTOR directional_light_vector;	// 16 bytes
	XMVECTOR directional_light_colour;	// 16 bytes
	XMVECTOR ambient_light_colour;		// 16 bytes
};	//TOTAL SIZE = 112 bytes

class model
{
private:
	ID3D11Device*				m_pD3DDevice;
	ID3D11DeviceContext*		m_pImmediateContext;

	ID3D11ShaderResourceView*	m_pTexture;
	ObjFileModel*				m_pObject;
	ID3D11VertexShader*			m_pVShader;
	ID3D11PixelShader*			m_pPShader;
	ID3D11InputLayout*			m_pInputLayout;
	ID3D11Buffer*				m_pConstantBuffer;
	XMVECTOR					m_directional_light_shines_from,
								m_directional_light_colour,
								m_ambient_light_colour;

	float						m_x = 0.0f,
								m_y = 0.0f,
								m_z = 0.0f,
								m_xAngle = 0.0f,
								m_yAngle = 0.0f,
								m_zAngle = 0.0f,
								m_scale = 1.0f;
	int							m_constantBufferSize = 64;

public:
	model();
	model(ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT LoadObjModel(char* filename);
	void Draw(XMMATRIX* view, XMMATRIX* projection);
	void AddTexture(char* filename);

	//////////////////////////////////////////////////////////////////////////////////////
	//	Sets values
	//////////////////////////////////////////////////////////////////////////////////////
	void SetXPos(float x);
	void SetYPos(float y);
	void SetZPos(float z);
	void SetXAngle(float x);
	void SetYAngle(float y);
	void SetZAngle(float z);
	void SetScale(float s);
	void SetDirectionalLight(
		XMVECTOR origin,
		XMVECTOR colour,
		XMVECTOR ambient);

	//////////////////////////////////////////////////////////////////////////////////////
	//	Gets values
	//////////////////////////////////////////////////////////////////////////////////////
	float GetXPos(void);
	float GetYPos(void);
	float GetZPos(void);
	float GetXAngle(void);
	float GetYAngle(void);
	float GetZAngle(void);
	float GetScale(void);

	//////////////////////////////////////////////////////////////////////////////////////
	// Increments values
	//////////////////////////////////////////////////////////////////////////////////////
	void AddXPos(float x);
	void AddYPos(float y);
	void AddZPos(float z);
	void AddXAngle(float x);
	void AddYAngle(float y);
	void AddZAngle(float z);
	void AddScale(float s);
	~model();
};

