#include "gameManager.h"



gameManager::gameManager()
{
}

gameManager::gameManager(HINSTANCE * hInstance, HWND * hWindow, ID3D11Device * device, ID3D11DeviceContext * context)
{
	InitialiseGraphics(device, context);
	m_pInput->InitInput(*hInstance, *hWindow);
	m_UIText = new Text2D("Assets/font1.bmp", device, context);
}

//////////////////////////////////////////////////////////////////////////////////////
//Init graphics
//////////////////////////////////////////////////////////////////////////////////////
HRESULT gameManager::InitialiseGraphics(ID3D11Device * device, ID3D11DeviceContext * context)
{
	HRESULT hr = S_OK;

	//Create texture
	/*D3DX11CreateShaderResourceViewFromFile(device,
		"assets/Lava_Tex.jpg",
		NULL,
		NULL,
		&m_pTexture0,
		NULL);*/

	m_pModel = new model(device, context);
	m_pModel->AddTexture((char*)"Assets/Rock_Tex.jpg");
	m_pModel->AddSampler(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_FLOAT32_MAX);
	m_pModel->LoadObjModel((char*)"Assets/Sphere.obj");

	m_pLava = new model(device, context);
	m_pLava->AddTexture((char*)"Assets/Lava_Tex.jpg");
	m_pLava->AddSampler(
		D3D11_FILTER_MIN_MAG_MIP_LINEAR,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_TEXTURE_ADDRESS_WRAP,
		D3D11_FLOAT32_MAX);
	m_pLava->LoadObjModel((char*)"Assets/cube.obj");

	//Define vertices of a triangle - screen coordinates -1.0 to +1.0
	//POS_COL_TEX_NORM_VERTEX vertices[] =
	//{
	//	// back face
	//	{ XMFLOAT3(-1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, 1.0f) },

	//	// front face
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(0.0f, 0.0f, -1.0f) },

	//	// left face
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(-1.0f, 0.0f, 0.0f) },

	//	// right face
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(1.0f, 0.0f, 0.0f) },
	//	// bottom face
	//	{ XMFLOAT3(1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, -1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, -1.0f, 0.0f) },

	//	// top face
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 0.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },
	//	{ XMFLOAT3(1.0f, 1.0f, 1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(1.0f, 0.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) },
	//	{ XMFLOAT3(-1.0f, 1.0f, -1.0f),	XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f),	XMFLOAT2(0.0f, 1.0f),	XMFLOAT3(0.0f, 1.0f, 0.0f) }
	//};

	////Set up and create vertex buffer
	//D3D11_BUFFER_DESC bufferDesc;
	//ZeroMemory(&bufferDesc, sizeof(bufferDesc));
	//bufferDesc.Usage = D3D11_USAGE_DYNAMIC;										//Allows use by CPU and GPU
	//bufferDesc.ByteWidth = sizeof(vertices);									//Set the total size of the buffer
	//bufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;							//Set the type of buffer to vertex buffer
	//bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;							//Allow access by the CPU
	//hr = device->CreateBuffer(&bufferDesc, NULL, &m_pVertexBuffer);		//Create the buffer

	//if (FAILED(hr)) return hr; //Return an error code if failed

	//						   //Copy the vertices into the buffer
	//D3D11_MAPPED_SUBRESOURCE ms;

	//// Create constant buffer
	//D3D11_BUFFER_DESC constant_buffer_desc;
	//ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));

	//constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	//constant_buffer_desc.ByteWidth = CONSTANT_BUFFER_SIZE;	// Must be a multiple of 16
	//constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	//hr = device->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer0);

	//if (FAILED(hr)) return hr;

	////Lock the buffer to allow writing
	//context->Map(m_pVertexBuffer, NULL, D3D11_MAP_WRITE_DISCARD, NULL, &ms);

	////Copy the data
	//memcpy(ms.pData, vertices, sizeof(vertices));

	////Unlock the buffer
	//context->Unmap(m_pVertexBuffer, NULL);

	//Load and compile the pixel and vertex shaders - use vs_5_0 to target DX11 hardware only
	ID3DBlob *VS, *PS, *error;
	hr = D3DX11CompileFromFile(
		"shaders.hlsl",
		0,
		0,
		"VShader",
		"vs_4_0",
		0,
		0,
		0,
		&VS,
		&error,
		0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	hr = D3DX11CompileFromFile(
		"shaders.hlsl",
		0,
		0,
		"PShader",
		"ps_4_0",
		0,
		0,
		0,
		&PS,
		&error,
		0);

	if (error != 0)//Check for shader compilation error
	{
		OutputDebugStringA((char*)error->GetBufferPointer());
		error->Release();
		if (FAILED(hr))//Don't fail if error is just a warning
		{
			return hr;
		}
	}

	//Create shader objects
	hr = device->CreateVertexShader(VS->GetBufferPointer(), VS->GetBufferSize(), NULL, &m_pVertexShader);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = device->CreatePixelShader(PS->GetBufferPointer(), PS->GetBufferSize(), NULL, &m_pPixelShader);
	if (FAILED(hr))
	{
		return hr;
	}

	//Set the shader objects as active
	context->VSSetShader(m_pVertexShader, 0, 0);
	context->PSSetShader(m_pPixelShader, 0, 0);

	//Create and set the input layout object
	/*D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};*/

	/*hr = device->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), VS->GetBufferPointer(), VS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}*/

	context->IASetInputLayout(m_pInputLayout);

	m_pCamera = new camera(0.0f, 0.0f, 0.0f, 0.0f, 0.002f, 0.25f, 0.010f);

	/*D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	device->CreateSamplerState(&sampler_desc, &m_pSampler0);*/

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Render frame
//////////////////////////////////////////////////////////////////////////////////////
void gameManager::RenderFrame(ID3D11DeviceContext* context, ID3D11RenderTargetView* backBuffer, ID3D11DepthStencilView* zBuffer, IDXGISwapChain* swapChain)
{
	XMMATRIX projection,
		world,
		view = m_pCamera->GetViewMatrix();
	XMMATRIX transpose;
	CONSTANT_BUFFER0 cb0_values;

	projection = XMMatrixPerspectiveFovLH(
		XMConvertToRadians(45.0),
		1280.0 / 720.0,
		1.0,
		100.0);

	// Clear the back buffer
	context->ClearRenderTargetView(backBuffer, rgba_clear_colour);

	context->ClearDepthStencilView(zBuffer, D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

	//Set vertex buffer
	/*UINT stride = sizeof(POS_COL_TEX_NORM_VERTEX);
	UINT offset = 0;
	context->IASetVertexBuffers(0, 1, &m_pVertexBuffer, &stride, &offset);*/

	//world = XMMatrixRotationZ(15);
	/*cb0_values.WorldViewProjection = world * view * projection;
	transpose = XMMatrixTranspose(world);*/ //model world matrix

	//cb0_values.directional_light_colour = m_directional_light_colour;
	//cb0_values.ambient_light_colour = m_ambient_light_colour;
	//cb0_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
	//cb0_values.directional_light_vector = XMVector3Normalize(cb0_values.directional_light_vector);

	 //upload new values for constant buffer
	//context->UpdateSubresource(m_pConstantBuffer0, 0, 0, &cb0_values, 0, 0);
	//context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer0);

	//Select which primitive type to use
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//context->PSSetSamplers(0, 1, &m_pSampler0);
	//context->PSSetShaderResources(0, 1, &m_pTexture0);

	//context->VSSetShader(m_pVertexShader, 0, 0);
	//context->PSSetShader(m_pPixelShader, 0, 0);
	//context->IASetInputLayout(m_pInputLayout);

	//Draw vertex buffer to back buffer
	//context->Draw(36, 0);

	/*world = XMMatrixRotationY(15);
	world *= XMMatrixTranslation(2, 10, 15);
	cb0_values.WorldViewProjection = world * view*projection;
	transpose = XMMatrixTranspose(world);*/	// model world matrix

	/*cb0_values.directional_light_colour = m_directional_light_colour;
	cb0_values.ambient_light_colour = m_ambient_light_colour;
	cb0_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
	cb0_values.directional_light_vector = XMVector3Normalize(cb0_values.directional_light_vector);*/

	//upload new values for constant buffer
	//context->UpdateSubresource(m_pConstantBuffer0, 0, 0, &cb0_values, 0, 0);
	//context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer0);

	//Select which primitive type to use
	//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	////Draw vertex buffer to back buffer
	//context->Draw(36, 0);

	//Render floor
	for (int z_index = -10; z_index < 10; z_index += 2)
	{
		for (int x_index = -10; x_index < 10; x_index += 2)
		{
			//world = XMMatrixTranslation(x_index, -2, z_index);
			//cb0_values.WorldViewProjection = world * view * projection;
			//transpose = XMMatrixTranspose(world);	// model world matrix

			//cb0_values.directional_light_colour = m_directional_light_colour;
			//cb0_values.ambient_light_colour = m_ambient_light_colour;
			//cb0_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, transpose);
			//cb0_values.directional_light_vector = XMVector3Normalize(cb0_values.directional_light_vector);

			//context->UpdateSubresource(m_pConstantBuffer0, 0, 0, &cb0_values, 0, 0);
			//context->VSSetConstantBuffers(0, 1, &m_pConstantBuffer0);

			//context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

			//context->PSSetSamplers(0, 1, &m_pSampler0);
			//context->PSSetShaderResources(0, 1, &m_pTexture0);

			//context->Draw(36, 0);
			m_pLava->SetXPos(x_index);
			m_pLava->SetYPos(m_floorY);
			m_pLava->SetZPos(z_index);

			m_pLava->IgnoreDirectionalLight();

			m_pLava->Draw(&view, &projection);
		}
	}

	//Render sphere
	m_pModel->SetXPos(0);
	m_pModel->SetZPos(7);
	m_pModel->SetYPos(1);

	m_pModel->SetDirectionalLight(
		m_directional_light_shines_from,
		m_directional_light_colour,
		m_ambient_light_colour);

	m_pModel->Draw(&view, &projection);

	// RENDER TEXT HERE

	m_UIText->AddText("Health", -1.0f, +1.0f, 0.1f);
	m_UIText->RenderText();

	// Display what has just been rendered
	swapChain->Present(0, 0);
}

//////////////////////////////////////////////////////////////////////////////////////
// Updates game logic
//////////////////////////////////////////////////////////////////////////////////////
void gameManager::UpdateLogic(HWND* hWindow)
{
	//Read input states
	m_pInput->ReadInputStates();

	//Get mouse inputs
	m_pCamera->Rotate(m_pInput->GetHorizontalMouseInput());
	m_pCamera->Pitch(m_pInput->GetVerticalMouseInput());

	//Get keyboard inputs
	if (m_pInput->IsKeyPressed(DIK_ESCAPE)) DestroyWindow(*hWindow);
	if (m_pInput->IsKeyPressed(DIK_W)) m_pCamera->Forward();
	if (m_pInput->IsKeyPressed(DIK_S)) m_pCamera->Backward();
	if (m_pInput->IsKeyPressed(DIK_A)) m_pCamera->StrafeLeft();
	if (m_pInput->IsKeyPressed(DIK_D)) m_pCamera->StrafeRight();
	if (m_pInput->IsKeyPressed(DIK_SPACE)) m_pCamera->Jump();

	//Apply gravity
	m_pCamera->UpdateVelocity(gravity, 0.0f);
}

//////////////////////////////////////////////////////////////////////////////////////
// Game loop
//////////////////////////////////////////////////////////////////////////////////////
void gameManager::RunGameLoop(HWND* hWindow, ID3D11DeviceContext* context, ID3D11RenderTargetView* backBuffer, ID3D11DepthStencilView* zBuffer, IDXGISwapChain* swapChain)
{
	UpdateLogic(hWindow);
	RenderFrame(context, backBuffer, zBuffer, swapChain);
}

//////////////////////////////////////////////////////////////////////////////////////
// Clean up D3D objects
//////////////////////////////////////////////////////////////////////////////////////
void gameManager::ShutdownD3D()
{
	if (m_pModel)
	{
		m_pModel = NULL;
		delete m_pModel;
	}

	if (m_pInputLayout)			m_pInputLayout->Release();
	if (m_pConstantBuffer0)		m_pConstantBuffer0->Release();
	if (m_pVertexBuffer)		m_pVertexBuffer->Release();
	if (m_pVertexShader)		m_pVertexShader->Release();
	if (m_pPixelShader)			m_pPixelShader->Release();
}


gameManager::~gameManager()
{
	
}
