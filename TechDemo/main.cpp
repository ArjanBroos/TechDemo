#include <Windows.h>
#include "Window.h"
#include <d3d11.h>
#include <cmath>
#include "Types.h"
#include <atlbase.h>
#include <d3dcompiler.h>

IDXGISwapChain* g_swapChain;
ID3D11Device* g_device;
ID3D11DeviceContext* g_context;
ID3D11RenderTargetView* g_renderTarget;
ID3D11Buffer* g_triangleVertexBuffer;
ID3D11VertexShader* g_vertexShader;
ID3D11PixelShader* g_pixelShader;
ID3D10Blob* g_vertexBuffer;
ID3D10Blob* g_pixelBuffer;
ID3D11InputLayout* g_vertexLayout;

D3D11_INPUT_ELEMENT_DESC g_layout[] =
{
	{"position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0}
};
UINT g_layoutSize = ARRAYSIZE(g_layout);

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

	CComPtr<ID3D11Texture2D> buffer;
	ThrowIfNotOk(
		g_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&buffer)),
		"Failed to retrieve buffer from swap chain."
	);

	ThrowIfNotOk(
		g_device->CreateRenderTargetView(buffer, NULL, &g_renderTarget),
		"Failed to create render target."
	);

	g_context->OMSetRenderTargets(1, &g_renderTarget, NULL);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(windowWidth);
	viewport.Height = static_cast<float>(windowHeight);

	g_context->RSSetViewports(1, &viewport);
}

void ReleaseObjects()
{
	g_swapChain->Release();
	g_device->Release();
	g_context->Release();
	g_renderTarget->Release();
	g_triangleVertexBuffer->Release();
	g_vertexShader->Release();
	g_pixelShader->Release();
	g_vertexBuffer->Release();
	g_pixelBuffer->Release();
	g_vertexLayout->Release();
}

void InitializeScene()
{
	ThrowIfNotOk(
		D3DCompileFromFile(L"vertexShader.vs", 0, 0, "vertexShader", "vs_5_0", 0, 0, &g_vertexBuffer, 0),
		"Could not compile vertex shader."
	);
	ThrowIfNotOk(
		D3DCompileFromFile(L"pixelShader.ps", 0, 0, "pixelShader", "ps_5_0", 0, 0, &g_pixelBuffer, 0),
		"Could not compile pixel shader"
	);

	ThrowIfNotOk(
		g_device->CreateVertexShader(g_vertexBuffer->GetBufferPointer(), g_vertexBuffer->GetBufferSize(), NULL, &g_vertexShader),
		"Could not create vertex shader"
	);
	ThrowIfNotOk(
		g_device->CreatePixelShader(g_pixelBuffer->GetBufferPointer(), g_pixelBuffer->GetBufferSize(), NULL, &g_pixelShader),
		"Could not create pixel shader"
	);

	g_context->VSSetShader(g_vertexShader, 0, 0);
	g_context->PSSetShader(g_pixelShader, 0, 0);

	Vertex vertices[] =
	{
		Vertex(0.f, 0.5f, 0.5f),
		Vertex(0.5f, -0.5f, 0.5f),
		Vertex(-0.5f, -0.5f, 0.5f)
	};

	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(vertexBufferDescription));
	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = sizeof(Vertex) * ARRAYSIZE(vertices);
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;

	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = vertices;
	ThrowIfNotOk(
		g_device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, &g_triangleVertexBuffer),
		"Could not create vertex buffer"
	);

	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	g_context->IASetVertexBuffers(0, 1, &g_triangleVertexBuffer, &stride, &offset);

	ThrowIfNotOk(
		g_device->CreateInputLayout(g_layout, g_layoutSize, g_vertexBuffer->GetBufferPointer(),
			g_vertexBuffer->GetBufferSize(), &g_vertexLayout),
		"Could not create input layout."
	);

	g_context->IASetInputLayout(g_vertexLayout);

	g_context->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
}

void UpdateScene()
{
}

void DrawScene()
{
	g_context->ClearRenderTargetView(g_renderTarget, Color::Black());
	g_context->Draw(3, 0);
	g_swapChain->Present(0, 0);
}
