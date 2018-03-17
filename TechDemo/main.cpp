#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include <cmath>

IDXGISwapChain* g_swapChain;
ID3D11Device* g_device;
ID3D11DeviceContext* g_context;
ID3D11RenderTargetView* g_renderTarget;
float red = 0.f;
float green = 0.f;
float blue = 0.f;

void InitializeDirect3D(HINSTANCE instanceHandle, unsigned windowWidth,
	unsigned windowHeight, HWND windowHandle);
void ReleaseObjects();
void InitializeScene();
void UpdateScene();
void DrawScene();

int WINAPI WinMain(HINSTANCE instanceHandle, HINSTANCE previousInstanceHandle,
	LPSTR commandLine, int showWindow)
{
	const unsigned WindowWidth = 800;
	const unsigned WindowHeight = 600;
	Window window(instanceHandle, L"ArjanTechDemoWindow", L"Arjan's Tech Demo", WindowWidth, WindowHeight);

	InitializeDirect3D(instanceHandle, WindowWidth, WindowHeight, window.GetHandle());
	InitializeScene();

	while (!window.UserHasQuit())
	{
		window.ProcessMessages();
		UpdateScene();
		DrawScene();
	}

	ReleaseObjects();

	return 0;
}

void ThrowIfNotOk(HRESULT result, const std::string& message)
{
	if (result != S_OK)
	{
		throw std::runtime_error(message);
	}
}

void InitializeDirect3D(HINSTANCE instanceHandle, unsigned windowWidth,
	unsigned windowHeight, HWND windowHandle)
{
	DXGI_MODE_DESC bufferDescription;
	ZeroMemory(&bufferDescription, sizeof(DXGI_MODE_DESC));
	bufferDescription.Width = windowWidth;
	bufferDescription.Height = windowHeight;
	bufferDescription.RefreshRate.Numerator = 60;
	bufferDescription.RefreshRate.Denominator = 1;
	bufferDescription.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	bufferDescription.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	bufferDescription.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

	DXGI_SWAP_CHAIN_DESC swapChainDescription;
	ZeroMemory(&swapChainDescription, sizeof(DXGI_SWAP_CHAIN_DESC));
	swapChainDescription.BufferDesc = bufferDescription;
	swapChainDescription.SampleDesc.Count = 1;
	swapChainDescription.SampleDesc.Quality = 0;
	swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
	swapChainDescription.BufferCount = 1;
	swapChainDescription.OutputWindow = windowHandle;
	swapChainDescription.Windowed = true;
	swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_SEQUENTIAL;
	swapChainDescription.Flags = 0;

	ThrowIfNotOk(
		D3D11CreateDeviceAndSwapChain(nullptr,
			D3D_DRIVER_TYPE_HARDWARE,
			NULL,
			D3D11_CREATE_DEVICE_DEBUG,
			NULL,
			NULL,
			D3D11_SDK_VERSION,
			&swapChainDescription,
			&g_swapChain,
			&g_device,
			NULL,
			&g_context),
		"Failed to create Direct3D11 device and swap chain."
	);

	ThrowIfNotOk(
		g_swapChain->ResizeBuffers(1, windowWidth, windowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, NULL),
		"Could not resize buffers."
	);

	ID3D11Texture2D* buffer;
	ThrowIfNotOk(
		g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer)),
		"Failed to retrieve buffer from swap chain."
	);

	ThrowIfNotOk(
		g_device->CreateRenderTargetView(buffer, NULL, &g_renderTarget),
		"Failed to create render target."
	);

	buffer->Release();
}

void ReleaseObjects()
{
	g_swapChain->Release();
	g_device->Release();
	g_context->Release();
}

void InitializeScene()
{
}

void UpdateScene()
{
	red = fmod(red + 0.00005f, 1.f);
	green = fmod(green + 0.00002f, 1.f);
	blue = fmod(blue + 0.00001f, 1.f);
}

void DrawScene()
{
	float color[4] = { red, green, blue, 1.f };
	g_context->OMSetRenderTargets(1, &g_renderTarget, NULL);
	g_context->ClearRenderTargetView(g_renderTarget, color);
	g_swapChain->Present(0, 0);
}
