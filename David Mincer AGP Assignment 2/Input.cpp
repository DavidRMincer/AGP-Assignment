#include "Input.h"



Input::Input()
{
}

//////////////////////////////////////////////////////////////////////////////////////
//Initialise input
//////////////////////////////////////////////////////////////////////////////////////
HRESULT Input::InitInput(HINSTANCE hinstance, HWND hwnd)
{
	HRESULT hr;

	ZeroMemory(m_keyboard_keys_state, sizeof(m_keyboard_keys_state));

	hr = DirectInput8Create(
		hinstance,
		DIRECTINPUT_VERSION,
		IID_IDirectInput8,
		(void**)&m_direct_input,
		NULL);
	if (FAILED(hr)) return hr;

	//Keyboard Setup
	hr = m_direct_input->CreateDevice(
		GUID_SysKeyboard,
		&m_keyboard_device,
		NULL);
	if (FAILED(hr)) return hr;

	hr = m_keyboard_device->SetDataFormat(&c_dfDIKeyboard);
	if (FAILED(hr)) return hr;

	hr = m_keyboard_device->SetCooperativeLevel(
		hwnd,
		DISCL_FOREGROUND | DISCL_NONEXCLUSIVE);
	if (FAILED(hr)) return hr;

	hr = m_keyboard_device->Acquire();
	if (FAILED(hr)) return hr;

	//Mouse Setup
	hr = m_direct_input->CreateDevice(
		GUID_SysMouse,
		&m_mouse_device,
		NULL);
	if (FAILED(hr)) return hr;

	hr = m_mouse_device->SetDataFormat(&c_dfDIMouse);
	if (FAILED(hr)) return hr;

	hr = m_mouse_device->SetCooperativeLevel(
		hwnd,
		DISCL_FOREGROUND | DISCL_EXCLUSIVE);
	if (FAILED(hr)) return hr;

	hr = m_mouse_device->Acquire();
	if (FAILED(hr)) return hr;

	return S_OK;
}

//////////////////////////////////////////////////////////////////////////////////////
// Reads input states
//////////////////////////////////////////////////////////////////////////////////////
void Input::ReadInputStates(void)
{
	HRESULT hr;

	//Read keyboard state
	hr = m_keyboard_device->GetDeviceState(
		sizeof(m_keyboard_keys_state),
		(LPVOID)&m_keyboard_keys_state);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) m_keyboard_device->Acquire();
	}

	//Read mouse state
	hr = m_mouse_device->GetDeviceState(
		sizeof(m_mouse_state),
		(LPVOID)&m_mouse_state);

	if (FAILED(hr))
	{
		if ((hr == DIERR_INPUTLOST) || (hr == DIERR_NOTACQUIRED)) m_mouse_device->Acquire();
	}
}

//////////////////////////////////////////////////////////////////////////////////////
// Returns key pressed state
//////////////////////////////////////////////////////////////////////////////////////
bool Input::IsKeyPressed(unsigned char DI_keycode)
{
	return m_keyboard_keys_state[DI_keycode] & 0x80;
}

//////////////////////////////////////////////////////////////////////////////////////
// Returns horizontal mouse movement
//////////////////////////////////////////////////////////////////////////////////////
float Input::GetHorizontalMouseInput(void)
{
	return m_mouse_state.lX;
}

//////////////////////////////////////////////////////////////////////////////////////
// Returns vertical mouse movement
//////////////////////////////////////////////////////////////////////////////////////
float Input::GetVerticalMouseInput(void)
{
	return -m_mouse_state.lY;
}

Input::~Input()
{
	if (m_mouse_device)
	{
		m_mouse_device->Unacquire();
		m_mouse_device->Release();
	}

	if (m_keyboard_device)
	{
		m_keyboard_device->Unacquire();
		m_keyboard_device->Release();
	}

	if (m_direct_input) m_direct_input->Release();
}
