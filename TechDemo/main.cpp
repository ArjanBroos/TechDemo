#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include "Types.h"
#include <vector>
#include "Renderer.h"

void ReleaseObjects();
unsigned InitializeScene(Renderer& renderer);
void UpdateScene();
void DrawScene(Renderer& renderer, unsigned vertexCount);

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 800;
	const unsigned WindowHeight = 600;
	Window window(instanceHandle, L"ArjanTechDemoWindow", L"Arjan's Tech Demo", WindowWidth, WindowHeight);

	Renderer renderer(WindowWidth, WindowHeight, window.GetHandle());

	unsigned vertexCount = InitializeScene(renderer);

	while (!window.UserHasQuit())
	{
		window.ProcessMessages();
		UpdateScene();
		DrawScene(renderer, vertexCount);
	}

	ReleaseObjects();

	return 0;
}

void ReleaseObjects()
{
}

unsigned InitializeScene(Renderer& renderer)
{
	auto vertexShader = renderer.CreateVertexShaderFromPrecompiledFile("vertexShader.cso");
	auto pixelShader = renderer.CreatePixelShaderFromPrecompiledFile("pixelShader.cso");
	renderer.SetVertexShader(vertexShader.shader);
	renderer.SetPixelShader(pixelShader);

	std::vector<Vertex> vertices =
	{
		Vertex(Position(0.f, 0.5f, 0.5f), Color::Red()),
		Vertex(Position(0.5f, -0.5f, 0.5f), Color::Green()),
		Vertex(Position(-0.5f, -0.5f, 0.5f), Color::Blue())
	};

	auto vertexBuffer = renderer.CreateVertexBuffer(vertices);
	renderer.SetVertexBuffer(vertexBuffer);
	renderer.SetInputLayout(vertexShader.inputLayout);
	renderer.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	return static_cast<unsigned>(vertices.size());
}

void UpdateScene()
{
}

void DrawScene(Renderer& renderer, unsigned vertexCount)
{
	renderer.ClearBackBuffer(Color::Black());
	renderer.SetRenderTargetToBackBuffer();
	renderer.Draw(vertexCount);
	renderer.Present();
}