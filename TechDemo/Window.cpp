#include "Window.h"
#include <Windows.h>

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
	windowClass.hbrBackground = reinterpret_cast<HBRUSH>(COLOR_WINDOW);
	windowClass.lpszMenuName = NULL;
	windowClass.lpszClassName = windowClassName.c_str();
	windowClass.hIconSm = LoadIcon(NULL, IDI_WINLOGO);
	if (!RegisterClassEx(&windowClass))
	{
		throw std::runtime_error("Could not register window class.");
	}
}

Window::Window(HINSTANCE instanceHandle, const std::string & name, const std::string & title,
	unsigned width, unsigned height)
	: m_userHasQuit(false)
{
	RegisterWindowClass(instanceHandle, name);

	m_handle = CreateWindowEx(NULL, name.c_str(),
		title.c_str(), WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT,
		width, height, NULL, NULL, instanceHandle, NULL);
	if (!m_handle)
	{
		throw std::runtime_error("Could not create window handle.");
	}

	ShowWindow(m_handle, SW_SHOW);
	UpdateWindow(m_handle);
}

void Window::ProcessMessages()
{
	MSG message;
	ZeroMemory(&message, sizeof(MSG));
	while (PeekMessage(&message, NULL, 0, 0, PM_REMOVE))
	{
		if (message.message == WM_QUIT)
		{
			m_userHasQuit = true;
		}
		TranslateMessage(&message);
		DispatchMessage(&message);
	}
}

HWND Window::GetHandle() const
{
	return m_handle;
}

bool Window::UserHasQuit() const
{
	return m_userHasQuit;
}
