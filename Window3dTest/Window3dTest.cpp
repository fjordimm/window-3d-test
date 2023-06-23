
#include <windows.h>
#include <gdiplus.h>
#include "WorldManager.h"

constexpr LPCWSTR MYWINDOW_SZCLASSNAME = L"ThreeDTest";
constexpr int MYWINDOW_INIT_WIDTH = 900;
constexpr int MYWINDOW_INIT_HEIGHT = 600;
constexpr LPCWSTR MYWINDOW_TITLETEXT = L"3D Test";

constexpr UINT_PTR TICK_TIMER_ID = 1;
constexpr UINT CLOCKS_PER_TICK = 100;

static World::WorldManager worldManager(MYWINDOW_INIT_WIDTH, MYWINDOW_INIT_HEIGHT);

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	Gdiplus::GdiplusStartupInput gdiStartupInput;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gdiStartupInput, nullptr);

	WNDCLASSEX wincl;
	{
		wincl.hInstance = hThisInstance;
		wincl.lpszClassName = MYWINDOW_SZCLASSNAME;
		wincl.lpfnWndProc = WindowProcedure;
		wincl.style = CS_DBLCLKS;
		wincl.cbSize = sizeof(WNDCLASSEX);

		// Using Window's default color as the background:
		wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;
		// Using default icon and mouse-pointer:
		wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
		wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
		// No menu:
		wincl.lpszMenuName = NULL;
		// No extra bytes after the window class structure or window instance:
		wincl.cbClsExtra = 0;
		wincl.cbWndExtra = 0;

		// Register the window class, and if it fails quit the program
		if (!RegisterClassEx(&wincl))
		{ return 0; }
	}

	HWND hwnd = CreateWindowEx
	(
		0,						// Extended possibilites for variation
		MYWINDOW_SZCLASSNAME,	// Class name
		MYWINDOW_TITLETEXT,		// Title Text
		WS_OVERLAPPEDWINDOW,	// Normal window
		CW_USEDEFAULT,			// Default (random?) initial x-pos
		CW_USEDEFAULT,			// Default (random?) initial y-pos
		MYWINDOW_INIT_WIDTH,	// Window width
		MYWINDOW_INIT_HEIGHT,	// Window height
		HWND_DESKTOP,			// The window is a child-window to desktop
		NULL,					// No menu
		hThisInstance,			// Program Instance handler
		NULL					// No Window Creation data
	);

	SetTimer(hwnd, TICK_TIMER_ID, CLOCKS_PER_TICK, NULL);

	ShowWindow(hwnd, nFunsterStil);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg); // Translate virtual-key messages into character messages
		DispatchMessage(&msg); // Send message to WindowProcedure
	}

	Gdiplus::GdiplusShutdown(gdiToken);

	KillTimer(hwnd, TICK_TIMER_ID);

	// The program return-value is 0 - The value that PostQuitMessage() gave
	return msg.wParam;
}

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		worldManager.drawToWindow(hdc);
		EndPaint(hwnd, &ps);
		break;
	case WM_KEYDOWN:
		worldManager.keydown(wParam);
		break;
	case WM_KEYUP:
		worldManager.keyup(wParam);
		break;
	case WM_SIZE:
		worldManager.windowResized(LOWORD(lParam), HIWORD(lParam));
		break;
	case WM_TIMER:
		if (wParam == TICK_TIMER_ID)
		{ InvalidateRect(hwnd, NULL, FALSE); /* Updates the window */ }
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, message, wParam, lParam);
	}
}
