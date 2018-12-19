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
	ID3D11Buffer*				g_pVertexBuffer;
	ID3D11Buffer*				g_pConstantBuffer0;
	ID3D11VertexShader*			g_pVertexShader;
	ID3D11PixelShader*			g_pPixelShader;
	ID3D11InputLayout*			g_pInputLayout;
	ID3D11ShaderResourceView*	m_pTexture0;
	ID3D11SamplerState*			m_pSampler0;

	camera*						m_pCamera;
	Input*						m_pInput = new Input();
	XMVECTOR					m_directional_light_shines_from = XMVectorSet(0.0f, -10.0f, 0.0f, 1.0f),
								m_directional_light_colour = XMVectorSet(0.9f, 0.3f, 0.05f, 1.0f),
								m_ambient_light_colour = XMVectorSet(0.3f, 0.3f, 0.3f, 1.0f);
	Text2D*						m_UIText = nullptr;
	float						degrees = 15.0f,
								cube1Z = 10.0f,
								gravity = 0.000005f,
								lightZ = 45.0f;
	const int					CONSTANT_BUFFER_SIZE = 112;

public:
	gameManager();
	gameManager(HINSTANCE* hInstance, HWND* hWindow,
		ID3D11Device* device, ID3D11DeviceContext* context);
	HRESULT InitialiseGraphics(ID3D11Device* device, ID3D11DeviceContext* context);
	void RenderFrame(ID3D11DeviceContext* context, ID3D11RenderTargetView* backBuffer,
		ID3D11DepthStencilView* zBuffer, IDXGISwapChain* swapChain);
	void UpdateLogic(HWND* hWindow);
	void RunGameLoop(HWND* hWindow, ID3D11DeviceContext* context,
		ID3D11RenderTargetView* backBuffer, ID3D11DepthStencilView* zBuffer,
		IDXGISwapChain* swapChain);
	void ShutdownD3D();
	~gameManager();
};

