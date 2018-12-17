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
#include "Input.h"

// Define vertex structure
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

class gameManager
{
private:
	/*D3D_DRIVER_TYPE				g_driverType = D3D_DRIVER_TYPE_NULL;
	D3D_FEATURE_LEVEL			g_featureLevel = D3D_FEATURE_LEVEL_11_0;*/
	HWND*						m_hWnd;
	ID3D11Device*				m_pD3DDevice = NULL;
	IDXGISwapChain*				m_pSwapChain = NULL;
	ID3D11DeviceContext*		m_pImmediateContext = NULL;
	ID3D11RenderTargetView*		m_pBackBufferRTView = NULL;
	ID3D11DepthStencilView*		m_pZBuffer;

	ID3D11Buffer*				g_pVertexBuffer;
	ID3D11Buffer*				g_pConstantBuffer0;
	ID3D11VertexShader*			g_pVertexShader;
	ID3D11PixelShader*			g_pPixelShader;
	ID3D11InputLayout*			g_pInputLayout;
	camera*						g_pCamera;
	Input*						g_pInput = new Input();
	ID3D11ShaderResourceView*	g_pTexture0;
	ID3D11SamplerState*			g_pSampler0;
	XMVECTOR					g_directional_light_shines_from,
								g_directional_light_colour,
								g_ambient_light_colour;
	Text2D*						m_UIText;
	float						redStuff = 1.0f,
								scaling = 1.0f,
								degrees = 15.0f,
								cube1Z = 10.0f,
								gravity = 0.000005f,
								lightZ = 45.0f;
	const int					CONSTANT_BUFFER_SIZE = 112;

public:
	gameManager();
	gameManager(HWND& hwnd, ID3D11Device* device,
		IDXGISwapChain* swapChain, ID3D11DeviceContext* immContext,
		ID3D11RenderTargetView* RTView, ID3D11DepthStencilView* zBuffer);
	HRESULT InitialiseGraphics();
	void RenderFrame(void);
	void UpdateLogic(void);
	void RunGameLoop(void);
	~gameManager();
};

