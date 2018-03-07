#include <Windows.h>
#include "Window.h"

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 960;
	const unsigned WindowHeight = 540;
	Window window(instanceHandle, "ArjanTechDemoWindow", "Arjan's Tech Demo", WindowWidth, WindowHeight);

	while (!window.UserHasQuit())
	{
		window.ProcessMessages();
	}

	return 0;
}