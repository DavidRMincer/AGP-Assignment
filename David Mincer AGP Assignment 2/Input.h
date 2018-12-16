#pragma once
#include <dinput.h>

class Input
{
private:
	IDirectInput8*				m_direct_input;
	IDirectInputDevice8*		m_keyboard_device;
	IDirectInputDevice8*		m_mouse_device;
	DIMOUSESTATE				m_mouse_state;
	unsigned char				m_keyboard_keys_state[256];

public:
	Input();
	HRESULT InitInput(HINSTANCE hinstance, HWND hwnd);
	void ReadInputStates(void);
	bool IsKeyPressed(unsigned char DI_keycode);
	float GetHorizontalMouseInput(void);
	float GetVerticalMouseInput(void);
	~Input();
};

