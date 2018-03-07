#include <Windows.h>
#include <string>

LRESULT CALLBACK WindowsProcedure(HWND windowHandle, UINT message,
	WPARAM wordParameter, LPARAM longParameter)
{
	switch (message)
	{
	case WM_KEYDOWN:
		if (wordParameter == VK_ESCAPE)
		{
			DestroyWindow(windowHandle);
		}
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProc(windowHandle, message, wordParameter, longParameter);
}

void RegisterWindowClass(HINSTANCE instanceHandle, const std::string& windowClassName)
{
	WNDCLASSEX windowClass;
	windowClass.cbSize = sizeof(WNDCLASSEX);
	windowClass.style = CS_HREDRAW | CS_VREDRAW;
	windowClass.lpfnWndProc = WindowsProcedure;
	windowClass.cbClsExtra = 0;
	windowClass.cbWndExtra = 0;
	windowClass.hInstance = instanceHandle;
	windowClass.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	windowClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW + 2);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = windowClassName.c_str();
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	if (!RegisterClassEx(&windowClass))
	{
		throw std::runtime_error("Could not register window class.");
	}
}

HWND InitializeWindow(HINSTANCE instanceHandle, int showWindow,
	unsigned width, unsigned height, const std::string& windowClassName,
	const std::string& windowTitle)
{
	RegisterWindowClass(instanceHandle, windowClassName);

	HWND windowHandle = CreateWindowEx(NULL, windowClassName.c_str(),
		windowTitle.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, NULL, instanceHandle, NULL);
	if (!windowHandle)
	{
		throw std::runtime_error("Could not create window handle.");
	}

	ShowWindow(windowHandle, showWindow);
	UpdateWindow(windowHandle);

	return windowHandle;
}

void MainLoop()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));
	while (true)
	{
		if (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
		{
			if (message.message == WM_QUIT)
			{
				break;
			}
			TranslateMessage(&message);
			DispatchMessage(&message);
		}
	}
}

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 960;
	const unsigned WindowHeight = 540;
	InitializeWindow(instanceHandle, showWindow, WindowWidth, WindowHeight,
		"TechDemoWindowClassName", "Arjan's Tech Demo");

	MainLoop();

	return 0;
}