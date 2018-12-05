//The #include order is important
#include "gameManager.h"

HINSTANCE					g_hInst = NULL;
HWND						g_hWnd = NULL;
float	g_windowWidth = 640,
		g_windowHeight = 480;

//////////////////////////////////////////////////////////////////////////////////////
// Entry point to the program. Initializes everything and goes into a message processing 
// loop. Idle time is used to render the scene.
//////////////////////////////////////////////////////////////////////////////////////
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	gameManager* game = new gameManager();

	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);

	if (FAILED(InitialiseWindow(hInstance, nCmdShow)))
	{
		DXTRACE_MSG("Failed to create Window");
		return 0;
	}

	if (FAILED(game->InitialiseD3D()))
	{
		DXTRACE_MSG("Failed to create Device");
		return 0;
	}

	if (FAILED(game->InitialiseGraphics()))
	{
		DXTRACE_MSG("Failed to initialise graphics");
		return 0;
	}

	// Main message loop
	MSG msg = { 0 };

	while (msg.message != WM_QUIT)
	{
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			game->ApplyGravity();
			game->RenderFrame();
		}
	}

	game->ShutdownD3D();

	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	PAINTSTRUCT ps;
	HDC hdc;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hWnd, &ps);
		EndPaint(hWnd, &ps);
		break;

	case WM_DESTROY:
		PostQuitMessage(0);
		break;

	//case WM_KEYDOWN:
	//	switch (wParam)
	//	{
	//	case VK_ESCAPE:
	//		DestroyWindow(g_hWnd);
	//		break;

	//		// W Key
	//	case 0x57:
	//		m_pCamera->Forward(m_pCamera->getMoveSpeed());
	//		break;

	//		// S Key
	//	case 0x53:
	//		m_pCamera->Forward(-m_pCamera->getMoveSpeed());
	//		break;

	//		// A Key
	//	case 0x41:
	//		m_pCamera->Strafe(-m_pCamera->getMoveSpeed());
	//		break;

	//		// D Key
	//	case 0x44:
	//		m_pCamera->Strafe(m_pCamera->getMoveSpeed());
	//		break;

	//		// LEFT Key
	//	case VK_LEFT:
	//		m_pCamera->Rotate(-m_pCamera->getRotateSpeed());
	//		break;

	//		// RIGHT Key
	//	case VK_RIGHT:
	//		m_pCamera->Rotate(m_pCamera->getRotateSpeed());
	//		break;

	//		// UP Key
	//	case VK_UP:
	//		m_pCamera->Pitch(m_pCamera->getRotateSpeed());
	//		break;

	//		// DOWN Key
	//	case VK_DOWN:
	//		m_pCamera->Pitch(-m_pCamera->getRotateSpeed());
	//		break;

	//		// SPACE Key
	//	case VK_SPACE:
	//		if (!m_pCamera->isJumping()) m_pCamera->Jump();
	//		break;

	//	default:
	//		break;
	//	}
	//	return 0;

	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
	}

	return 0;
}

HRESULT InitialiseWindow(HINSTANCE hInstance, int nCmdShow)
{
	// Give your app your own name
	char Name[100] = "David R Mincer\0";

	// Register class
	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.hInstance = hInstance;
	wcex.hCursor = LoadCursor(NULL, IDC_ARROW);
	//   wcex.hbrBackground = (HBRUSH )( COLOR_WINDOW + 1); // Needed for non-D3D apps
	wcex.lpszClassName = Name;

	if (!RegisterClassEx(&wcex)) return E_FAIL;

	// Create window
	g_hInst = hInstance;
	RECT rc = {
		0,
		0,
		g_windowWidth,
		g_windowHeight
	};
	AdjustWindowRect(&rc, WS_OVERLAPPEDWINDOW, FALSE);
	g_hWnd = CreateWindow(Name, g_WindowName, WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, rc.right - rc.left,
		rc.bottom - rc.top, NULL, NULL, hInstance, NULL);
	if (!g_hWnd)
		return E_FAIL;

	ShowWindow(g_hWnd, nCmdShow);

	return S_OK;
}
