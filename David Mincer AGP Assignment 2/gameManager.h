#pragma once
#include <d3d11.h>
#include <dxgi.h>
#include <d3dx11.h>
#include <windows.h>
#include <dxerr.h>
#define _XM_NO_INTRINSICS_
#define XM_NO_ALIGNMENT
#include <xnamath.h>
#include "camera.h"
#include "text2D.h"

//////////////////////////////////////////////////////////////////////////////////////
//	Global Variables
//////////////////////////////////////////////////////////////////////////////////////


struct POS_COL_TEX_NORM_VERTEX//This will be added to and renamed in future tutorials
{
	XMFLOAT3	pos;
	XMFLOAT4	Col;
	XMFLOAT2	Texture0;
	XMFLOAT3	Normal;
};

// Const buffer structs. Pack to 16 bytes. Don't let any single element cross a 16 byte boundary
struct CONSTANT_BUFFER0
{
	XMMATRIX WorldViewProjection;		// 64 bytes
	XMVECTOR directional_light_vector;	// 16 bytes
	XMVECTOR directional_light_colour;	// 16 bytes
	XMVECTOR ambient_light_colour;		// 16 bytes
	// TOTAL SIZE = 112 bytes
};

// Rename for each tutorial – This will appear in the title bar of the window
char		g_WindowName[100] = "Fiery Facial\0";

class gameManager
{
private:
	HINSTANCE					m_hInst = NULL;
	HWND						m_hWnd = NULL;
	D3D_DRIVER_TYPE				m_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL			m_featureLevel = D3D_FEATURE_LEVEL_11_0;
	ID3D11Device*				m_pD3DDevice = NULL;
	ID3D11DeviceContext*		m_pImmediateContext = NULL;
	IDXGISwapChain*				m_pSwapChain = NULL;
	ID3D11RenderTargetView*		m_pBackBufferRTView = NULL;
	ID3D11Buffer*				m_pVertexBuffer;
	ID3D11Buffer*				m_pConstantBuffer0;
	ID3D11VertexShader*			m_pVertexShader;
	ID3D11PixelShader*			m_pPixelShader;
	ID3D11InputLayout*			m_pInputLayout;
	ID3D11DepthStencilView*		m_pZBuffer;
	camera*						m_pCamera;
	ID3D11ShaderResourceView*	m_pTexture0;
	ID3D11SamplerState*			m_pSampler0;
	Text2D*						m_2DText;
	XMVECTOR					m_directional_light_shines_from,
								m_directional_light_colour,
								m_ambient_light_colour;
	float						m_scaling = 1.0f,
								m_degrees = 15.0f,
								m_cube1Z = 10.0f,
								m_gravity = 0.000005f,
								m_lightZ = 45.0f;
	const int					CONSTANT_BUFFER_SIZE = 112;
public:

	gameManager();
	void ShutdownD3D();
	HRESULT InitialiseGraphics();
	void ApplyGravity(void);
	void RenderFrame(void);
	~gameManager();
};

