#pragma once
#include <d3d11.h>
#include <math.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>
#include "objfilemodel.h"
#include "camera.h"

struct POS_COL_TEX_NORM_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
	XMFLOAT2	Texture0;
	XMFLOAT3	Normal;
};

struct CONSTANT_BUFFER
{
	XMMATRIX WorldViewProjection;		// 64 bytes
	XMVECTOR directional_light_vector;	// 16 bytes
	XMVECTOR directional_light_colour;	// 16 bytes
	XMVECTOR ambient_light_colour;		// 16 bytes
										//TOTAL SIZE = 112 bytes
};

class skybox
{
private:
	ID3D11Device*				m_pD3DDevice;
	ID3D11DeviceContext*		m_pImmediateContext;

	ID3D11VertexShader*			m_pVertexShader;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11InputLayout*			m_pInputLayout;

	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pConstantBuffer;

	ID3D11RasterizerState		*m_pRasterSolid = 0,
								*m_pRasterSkybox = 0;
	ID3D11DepthStencilState		*m_pDepthWriteSolid = 0,
								*m_pDepthWriteSkybox = 0;

	ID3D11ShaderResourceView*	m_pTexture;
	ID3D11SamplerState*			m_pSampler;

	float						m_scale = 3.0f;
	const int					m_constantBufferSize = 64;

public:
	skybox(ID3D11Device* device, ID3D11Buffer* vBuffer,
		ID3D11Buffer* cBuffer, ID3D11DeviceContext* context);
	HRESULT InitSkybox();
	void Draw(XMMATRIX* view, XMMATRIX* projection, camera* cam);
	~skybox();
};

