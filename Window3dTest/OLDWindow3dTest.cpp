/*
#include <windows.h>
#include <gdiplus.h>

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);
void drawFunction(HDC hdc);

/*  Make the class name into a global variable  */
LPCWSTR szClassName = L"ThreeDTest";

int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nFunsterStil)
{
	// GDI+ stuff
	Gdiplus::GdiplusStartupInput gdiStartupInput;
	ULONG_PTR gdiToken;
	Gdiplus::GdiplusStartup(&gdiToken, &gdiStartupInput, nullptr);

	HWND hwnd;               /* This is the handle for our window */
	MSG messages;            /* Here messages to the application are saved */
	WNDCLASSEX wincl;        /* Data structure for the windowclass */

	/* The Window structure */
	wincl.hInstance = hThisInstance;
	wincl.lpszClassName = szClassName;
	wincl.lpfnWndProc = WindowProcedure;      /* This function is called by windows */
	wincl.style = CS_DBLCLKS;                 /* Catch double-clicks */
	wincl.cbSize = sizeof(WNDCLASSEX);

	/* Use default icon and mouse-pointer */
	wincl.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hIconSm = LoadIcon(NULL, IDI_APPLICATION);
	wincl.hCursor = LoadCursor(NULL, IDC_ARROW);
	wincl.lpszMenuName = NULL;                 /* No menu */
	wincl.cbClsExtra = 0;                      /* No extra bytes after the window class */
	wincl.cbWndExtra = 0;                      /* structure or the window instance */
	/* Use Windows's default color as the background of the window */
	wincl.hbrBackground = (HBRUSH)COLOR_BACKGROUND;

	/* Register the window class, and if it fails quit the program */
	if (!RegisterClassEx(&wincl))
	return 0;

	/* The class is registered, let's create the program*/
	hwnd = CreateWindowEx(
		0,                   /* Extended possibilites for variation */
		szClassName,         /* Classname */
		L"3D Test",			 /* Title Text */
		WS_OVERLAPPEDWINDOW, /* default window */
		CW_USEDEFAULT,       /* Windows decides the position */
		CW_USEDEFAULT,       /* where the window ends up on the screen */
		544,                 /* The programs width */
		375,                 /* and height in pixels */
		HWND_DESKTOP,        /* The window is a child-window to desktop */
		NULL,                /* No menu */
		hThisInstance,       /* Program Instance handler */
		NULL                 /* No Window Creation data */
	);

	/* Make the window visible on the screen */
	ShowWindow(hwnd, nFunsterStil);

	/* Run the message loop. It will run until GetMessage() returns 0 */
	while (GetMessage(&messages, NULL, 0, 0))
	{
		/* Translate virtual-key messages into character messages */
		TranslateMessage(&messages);
		/* Send message to WindowProcedure */
		DispatchMessage(&messages);
	}

	// Other GDI+ stuff
	Gdiplus::GdiplusShutdown(gdiToken);

	/* The program return-value is 0 - The value that PostQuitMessage() gave */
	return messages.wParam;
}


/*  This function is called by the Windows function DispatchMessage()  */

LRESULT CALLBACK WindowProcedure(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	HDC hdc;
	PAINTSTRUCT ps;

	switch (message)                  /* handle the messages */
	{
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		drawFunction(hdc);
		EndPaint(hwnd, &ps);
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);       /* send a WM_QUIT to the message queue */
		break;
	default:                      /* for messages that we don't deal with */
		return DefWindowProc(hwnd, message, wParam, lParam);
	}

	return 0;
}

void drawFunction(HDC hdc)
{
	Gdiplus::Graphics gf(hdc);
	Gdiplus::Pen pen(Gdiplus::Color(255, 255, 0, 255));
	Gdiplus::SolidBrush brush(Gdiplus::Color(255, 0, 255, 0));

	gf.DrawLine(&pen, 0, 0, 500, 500);
}
*/