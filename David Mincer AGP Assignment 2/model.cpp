#include "model.h"



model::model()
{
}

//////////////////////////////////////////////////////////////////////////////////////
//	Custom constructor
//////////////////////////////////////////////////////////////////////////////////////
model::model(ID3D11Device * device, ID3D11DeviceContext * context)
{
	m_pD3DDevice = device;
	m_pImmediateContext = context;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Load object model & compile model shaders
//////////////////////////////////////////////////////////////////////////////////////
HRESULT model::LoadObjModel(char * filename)
{
	HRESULT hr;

	m_pObject = new ObjFileModel(filename, m_pD3DDevice, m_pImmediateContext);

	if (m_pObject->filename == "FILE NOT LOADED")
		return S_FALSE;

	//Load and compile the pixel and vertex shaders
	ID3DBlob *MVS, *MPS, *error;

	hr = D3DX11CompileFromFile(
		"model_shaders.hlsl",
		0,
		0,
		"ModelVS",
		"vs_4_0",
		0,
		0,
		0,
		&MVS,
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
		"model_shaders.hlsl",
		0,
		0,
		"ModelPS",
		"ps_4_0",
		0,
		0,
		0,
		&MPS,
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
	hr = m_pD3DDevice->CreateVertexShader(MVS->GetBufferPointer(), MVS->GetBufferSize(), NULL, &m_pVShader);
	if (FAILED(hr))
	{
		return hr;
	}

	hr = m_pD3DDevice->CreatePixelShader(MPS->GetBufferPointer(), MPS->GetBufferSize(), NULL, &m_pPShader);
	if (FAILED(hr))
	{
		return hr;
	}

	//Create and set the input layout object
	D3D11_INPUT_ELEMENT_DESC iedesc[] =
	{
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT,0,0,D3D11_INPUT_PER_VERTEX_DATA,0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "NORMAL", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};

	hr = m_pD3DDevice->CreateInputLayout(iedesc, ARRAYSIZE(iedesc), MVS->GetBufferPointer(), MVS->GetBufferSize(), &m_pInputLayout);
	if (FAILED(hr))
	{
		return hr;
	}

	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	//Create constant buffer
	D3D11_BUFFER_DESC constant_buffer_desc;
	ZeroMemory(&constant_buffer_desc, sizeof(constant_buffer_desc));

	constant_buffer_desc.Usage = D3D11_USAGE_DEFAULT;
	constant_buffer_desc.ByteWidth = m_constantBufferSize;
	constant_buffer_desc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;

	hr = m_pD3DDevice->CreateBuffer(&constant_buffer_desc, NULL, &m_pConstantBuffer);

	if (FAILED(hr)) return hr;

	//Create sampler
	/*D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampler_desc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampler_desc.MaxLOD = D3D11_FLOAT32_MAX;

	m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler);*/

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Load object model & compile model shaders
//////////////////////////////////////////////////////////////////////////////////////
void model::Draw(XMMATRIX * view, XMMATRIX * projection)
{
	XMMATRIX world,
		model_transpose;
	MODEL_CONSTANT_BUFFER model_cb_values;

	//Scale
	world = XMMatrixScaling(
		m_scale,
		m_scale,
		m_scale);
	//Rotate
	world *= XMMatrixRotationRollPitchYaw(
		m_xAngle,
		m_yAngle,
		m_zAngle);
	//Translate
	world *= XMMatrixTranslation(
		m_x,
		m_y,
		m_z);

	//Create model constant buffer
	model_cb_values.WorldViewProjection = world * (*view) * (*projection);
	model_transpose = XMMatrixTranspose(world);

	//Sets model constant buffer directional lighting
	model_cb_values.directional_light_colour = m_directional_light_colour;
	model_cb_values.ambient_light_colour = m_ambient_light_colour;
	model_cb_values.directional_light_vector = XMVector3Transform(m_directional_light_shines_from, model_transpose);
	model_cb_values.directional_light_vector = XMVector3Normalize(model_cb_values.directional_light_vector);
	
	//Upload new values for constant buffer
	m_pImmediateContext->VSSetConstantBuffers(0, 1, &m_pConstantBuffer);
	m_pImmediateContext->UpdateSubresource(
		m_pConstantBuffer,
		0,
		0,
		&model_cb_values,
		0,
		0);

	//Select which primitive type to use
	m_pImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	//Set sampler and texture as active
	m_pImmediateContext->PSSetSamplers(0, 1, &m_pSampler);
	m_pImmediateContext->PSSetShaderResources(0, 1, &m_pTexture);

	//Set the shader objects as active
	m_pImmediateContext->VSSetShader(m_pVShader, 0, 0);
	m_pImmediateContext->PSSetShader(m_pPShader, 0, 0);

	//Set the input layout as active
	m_pImmediateContext->IASetInputLayout(m_pInputLayout);

	//Draw object
	m_pObject->Draw();
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set model texture
//////////////////////////////////////////////////////////////////////////////////////
void model::AddTexture(char * filename)
{
	D3DX11CreateShaderResourceViewFromFile(m_pD3DDevice,
		filename,
		NULL,
		NULL,
		&m_pTexture,
		NULL);
}

void model::AddSampler(D3D11_FILTER filter, D3D11_TEXTURE_ADDRESS_MODE u, D3D11_TEXTURE_ADDRESS_MODE v, D3D11_TEXTURE_ADDRESS_MODE w, float maxLOD)
{
	D3D11_SAMPLER_DESC sampler_desc;
	ZeroMemory(&sampler_desc, sizeof(sampler_desc));
	sampler_desc.Filter = filter;
	sampler_desc.AddressU = u;
	sampler_desc.AddressV = v;
	sampler_desc.AddressW = w;
	sampler_desc.MaxLOD = maxLOD;

	m_pD3DDevice->CreateSamplerState(&sampler_desc, &m_pSampler);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set x position
//////////////////////////////////////////////////////////////////////////////////////
void model::SetXPos(float x)
{
	m_x = x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set y position
//////////////////////////////////////////////////////////////////////////////////////
void model::SetYPos(float y)
{
	m_y = y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set z position
//////////////////////////////////////////////////////////////////////////////////////
void model::SetZPos(float z)
{
	m_z = z;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set x angle
//////////////////////////////////////////////////////////////////////////////////////
void model::SetXAngle(float x)
{
	m_xAngle = x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set y angle
//////////////////////////////////////////////////////////////////////////////////////
void model::SetYAngle(float y)
{
	m_yAngle = y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set z angle
//////////////////////////////////////////////////////////////////////////////////////
void model::SetZAngle(float z)
{
	m_zAngle = z;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set scale value
//////////////////////////////////////////////////////////////////////////////////////
void model::SetScale(float s)
{
	m_scale = s;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set directional light values
//////////////////////////////////////////////////////////////////////////////////////
void model::SetDirectionalLight(XMVECTOR origin, XMVECTOR colour, XMVECTOR ambient)
{
	m_directional_light_shines_from = origin;
	m_directional_light_colour = colour;
	m_ambient_light_colour = ambient;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Set ambient and directional light to same colour
//////////////////////////////////////////////////////////////////////////////////////
void model::IgnoreDirectionalLight(void)
{
	m_directional_light_shines_from = XMVectorSet(0.0f, 0.0f, 0.0f, 1.0f),
	m_directional_light_colour = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f),
	m_ambient_light_colour = XMVectorSet(1.0f, 1.0f, 1.0f, 1.0f);
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get x position
//////////////////////////////////////////////////////////////////////////////////////
float model::GetXPos(void)
{
	return m_x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get y position
//////////////////////////////////////////////////////////////////////////////////////
float model::GetYPos(void)
{
	return m_y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get z position
//////////////////////////////////////////////////////////////////////////////////////
float model::GetZPos(void)
{
	return m_z;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get x angle
//////////////////////////////////////////////////////////////////////////////////////
float model::GetXAngle(void)
{
	return m_xAngle;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get y angle
//////////////////////////////////////////////////////////////////////////////////////
float model::GetYAngle(void)
{
	return m_yAngle;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get z angle
//////////////////////////////////////////////////////////////////////////////////////
float model::GetZAngle(void)
{
	return m_zAngle;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Get scale value
//////////////////////////////////////////////////////////////////////////////////////
float model::GetScale(void)
{
	return m_scale;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns ambient light origin
//////////////////////////////////////////////////////////////////////////////////////
XMVECTOR model::GetDLightOrigin(void)
{
	return m_directional_light_shines_from;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns directional light colour
//////////////////////////////////////////////////////////////////////////////////////
XMVECTOR model::GetDLightColour(void)
{
	return m_directional_light_colour;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Returns ambient light colour
//////////////////////////////////////////////////////////////////////////////////////
XMVECTOR model::GetAmbientLight(void)
{
	return m_ambient_light_colour;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds x to x position
//////////////////////////////////////////////////////////////////////////////////////
void model::AddXPos(float x)
{
	m_x += x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds y to y position
//////////////////////////////////////////////////////////////////////////////////////
void model::AddYPos(float y)
{
	m_y += y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds z to z position
//////////////////////////////////////////////////////////////////////////////////////
void model::AddZPos(float z)
{
	m_z += z;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds x to x angle
//////////////////////////////////////////////////////////////////////////////////////
void model::AddXAngle(float x)
{
	m_xAngle += x;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds y to y angle
//////////////////////////////////////////////////////////////////////////////////////
void model::AddYAngle(float y)
{
	m_yAngle += y;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds z to z angle
//////////////////////////////////////////////////////////////////////////////////////
void model::AddZAngle(float z)
{
	m_zAngle += z;
}

//////////////////////////////////////////////////////////////////////////////////////
//	Adds s to scale value
//////////////////////////////////////////////////////////////////////////////////////
void model::AddScale(float s)
{
	m_scale += s;
}


model::~model()
{
	if (m_pSampler) m_pSampler->Release();
	if (m_pTexture) m_pTexture->Release();

	if (m_pObject)
	{
		delete m_pObject;
		m_pObject = NULL;
	}

	m_pPShader->Release();
	m_pVShader->Release();
}
