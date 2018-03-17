#pragma once

#include <Windows.h>
#include <string>

class Window
{
public:
	Window(HINSTANCE instanceHandle, const std::wstring& name, const std::wstring& title,
		unsigned width, unsigned height);

	void ProcessMessages();
	bool UserHasQuit() const;

	HWND GetHandle() const;

private:
	HWND m_handle;
	bool m_userHasQuit;
};