#pragma once

#include <Windows.h>
#include <string>

class Window
{
public:
	Window(HINSTANCE instanceHandle, const std::string& name, const std::string& title,
		unsigned width, unsigned height);

	void ProcessMessages();
	bool UserHasQuit();

private:
	bool m_userHasQuit;
};