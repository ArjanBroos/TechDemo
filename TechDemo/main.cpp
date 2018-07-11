#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include "Types.h"
#include <vector>
#include "Renderer.h"
#include "ShaderCompiler.h"
#include "Mesh.h"

void ReleaseObjects();
Mesh InitializeScene(Renderer& renderer);
void UpdateScene();
void DrawScene(Renderer& renderer, unsigned indexCount);

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 800;
	const unsigned WindowHeight = 600;
	Window window(instanceHandle, L"ArjanTechDemoWindow", L"Arjan's Tech Demo", WindowWidth, WindowHeight);

	Renderer renderer(WindowWidth, WindowHeight, window.GetHandle());

	Mesh mesh = InitializeScene(renderer);

	while (!window.UserHasQuit())
	{
		window.ProcessMessages();
		UpdateScene();
		DrawScene(renderer, mesh.GetNumberOfIndices());
	}

	ReleaseObjects();

	return 0;
}

void ReleaseObjects()
{
}

Mesh InitializeScene(Renderer& renderer)
{
	ShaderCompiler shaderCompiler(renderer.GetDevice());
	auto vertexShader = shaderCompiler.CreateVertexShaderFromPrecompiledFile("vertexShader.cso");
	auto pixelShader = shaderCompiler.CreatePixelShaderFromPrecompiledFile("pixelShader.cso");

	renderer.SetVertexShader(vertexShader.shader);
	renderer.SetInputLayout(vertexShader.inputLayout);
	renderer.SetPixelShader(pixelShader);

	std::vector<Vertex> vertices =
	{
		Vertex(Position(-0.5f, -0.5f, 0.5f), Color::Red()),
		Vertex(Position(-0.5f, 0.5f, 0.5f), Color::Green()),
		Vertex(Position(0.5f, 0.5f, 0.5f), Color::Blue()),
		Vertex(Position(0.5f, -0.5f, 0.5f), Color::Yellow())
	};

	std::vector<DWORD> indices =
	{
		0, 1, 2,
		0, 2, 3
	};

	Mesh mesh(renderer, vertices, indices);
	mesh.SetBuffers();

	return mesh;
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