#include "cef_app.h"
#include "example.hpp"

CefRefPtr<ExampleHandler> g_handler;
CefRefPtr<CefRequestContextHandler> context_handler;

void
destroy(void)
{
	CefQuitMessageLoop();
}

LRESULT
CALLBACK WndProc(HWND hwnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	switch (msg) {
	case WM_CLOSE:
		DestroyWindow(hwnd);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hwnd, msg, wParam, lParam);
	}
	return 0;
}

int
WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstnce,
	LPSTR lpCmdLine, int nCmdShow)
{
	CefRefPtr<CefRequestContext> context = CefRequestContext::CreateContext(context_handler);
	CefMainArgs main_args(hInstance);
	
	int exitCode = CefExecuteProcess(main_args, NULL, NULL);
	if (exitCode >= 0)
		return exitCode;
	
	CefSettings settings;
	CefInitialize(main_args, settings, NULL, NULL);
	
	CefBrowserSettings browserSettings;
	CefWindowInfo info;
	g_handler = new ExampleHandler();

	const char *g_szClassName = "myWindowClass";
	WNDCLASSEX wc = {};
	wc.cbSize			= sizeof(WNDCLASSEX);
	wc.style			= 0;
	wc.lpfnWndProc		= WndProc;
	wc.cbClsExtra		= 0;
	wc.cbWndExtra		= 0;
	wc.hInstance		= hInstance;
	wc.hIcon			= LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor			= LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground	= (HBRUSH) (COLOR_WINDOW + 1);
	wc.lpszMenuName		= NULL;
	wc.lpszClassName	= g_szClassName;
	wc.hIconSm			= LoadIcon(NULL, IDI_APPLICATION);

	if (!RegisterClassEx(&wc)) {
		MessageBox(NULL, "Window Registration Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	HWND hwnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		g_szClassName,
		"The title of my window",
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, 240, 120,
		NULL, NULL, hInstance, NULL);

	if (hwnd == NULL) {
		MessageBox(NULL, "Window Creation Failed!", "Error!",
			MB_ICONEXCLAMATION | MB_OK);
		return 0;
	}

	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	
	RECT rect;
	GetClientRect(hwnd, &rect);
	info.SetAsChild(hwnd, rect);
	CefBrowserHost::CreateBrowserSync(info, g_handler.get(), "http://www.github.com", browserSettings, context);
	
	CefRunMessageLoop();
	CefShutdown();
	return 0;
}
