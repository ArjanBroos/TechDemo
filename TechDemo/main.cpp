#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include "Types.h"
#include <vector>
#include "Renderer.h"

void ReleaseObjects();
unsigned InitializeScene(Renderer& renderer);
void UpdateScene();
void DrawScene(Renderer& renderer, unsigned indexCount);

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 800;
	const unsigned WindowHeight = 600;
	Window window(instanceHandle, L"ArjanTechDemoWindow", L"Arjan's Tech Demo", WindowWidth, WindowHeight);

	Renderer renderer(WindowWidth, WindowHeight, window.GetHandle());

	unsigned indexCount = InitializeScene(renderer);

	while (!window.UserHasQuit())
	{
		window.ProcessMessages();
		UpdateScene();
		DrawScene(renderer, indexCount);
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
		Vertex(Position(-0.5f, -0.5f, 0.5f), Color::Red()),
		Vertex(Position(-0.5f, 0.5f, 0.5f), Color::Green()),
		Vertex(Position(0.5f, 0.5f, 0.5f), Color::Blue()),
		Vertex(Position(0.5f, -0.5f, 0.5f), Color::Yellow())
	};

	auto vertexBuffer = renderer.CreateVertexBuffer(vertices);
	renderer.SetVertexBuffer(vertexBuffer);
	renderer.SetInputLayout(vertexShader.inputLayout);
	renderer.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	std::vector<DWORD> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	auto indexBuffer = renderer.CreateIndexBuffer(indices);
	renderer.SetIndexBuffer(indexBuffer);

	return static_cast<unsigned>(indices.size());
}

void UpdateScene()
{
}

void DrawScene(Renderer& renderer, unsigned indexCount)
{
	renderer.ClearBackBuffer(Color::Black());
	renderer.ClearDepthStencilView();
	renderer.SetRenderTargetToBackBuffer();
	renderer.Draw(indexCount);
	renderer.Present();
}