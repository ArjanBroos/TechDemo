#include "Renderer.h"
#include "Utility.h"

Renderer::Renderer(unsigned windowWidth, unsigned windowHeight, HWND windowHandle)
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
			&m_swapChain,
			&m_device,
			NULL,
			&m_context),
		"Failed to create Direct3D11 device and swap chain."
	);

	ThrowIfNotOk(
		m_swapChain->ResizeBuffers(1, windowWidth, windowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, NULL),
		"Could not resize buffers."
	);

	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfNotOk(
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer),
		"Failed to retrieve buffer from swap chain."
	);

	ThrowIfNotOk(
		m_device->CreateRenderTargetView(backBuffer.Get(), NULL, &m_backBufferRenderTarget),
		"Failed to create render target."
	);

	D3D11_VIEWPORT viewport;
	ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(windowWidth);
	viewport.Height = static_cast<float>(windowHeight);

	m_context->RSSetViewports(1, &viewport);
}

void Renderer::SetRenderTarget(ComPtr<ID3D11RenderTargetView> renderTarget)
{
	m_context->OMSetRenderTargets(1, renderTarget.GetAddressOf(), NULL);
}

void Renderer::SetRenderTargetToBackBuffer()
{
	SetRenderTarget(m_backBufferRenderTarget);
}

VertexShader Renderer::CreateVertexShaderFromPrecompiledFile(const std::string & filename)
{
	VertexShader vertexShader;
	auto vertexShaderByteCode = ReadByteArray(filename);
	ThrowIfNotOk(
		m_device->CreateVertexShader(&vertexShaderByteCode[0], vertexShaderByteCode.size(), NULL, &vertexShader.shader),
		"Could not create vertex shader"
	);

	D3D11_INPUT_ELEMENT_DESC layout[] =
	{
		{ "position", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "color", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	UINT layoutSize = ARRAYSIZE(layout);

	ThrowIfNotOk(
		m_device->CreateInputLayout(layout, layoutSize, &vertexShaderByteCode[0],
			vertexShaderByteCode.size(), &vertexShader.inputLayout),
		"Could not create input layout."
	);
	return vertexShader;
}

ComPtr<ID3D11PixelShader> Renderer::CreatePixelShaderFromPrecompiledFile(const std::string & filename)
{
	auto pixelShaderByteCode = ReadByteArray(filename);
	ComPtr<ID3D11PixelShader> pixelShader;
	ThrowIfNotOk(
		m_device->CreatePixelShader(&pixelShaderByteCode[0], pixelShaderByteCode.size(), NULL, &pixelShader),
		"Could not create pixel shader"
	);
	return pixelShader;
}

void Renderer::SetVertexShader(ComPtr<ID3D11VertexShader> vertexShader)
{
	m_context->VSSetShader(vertexShader.Get(), 0, 0);
}

void Renderer::SetPixelShader(ComPtr<ID3D11PixelShader> pixelShader)
{
	m_context->PSSetShader(pixelShader.Get(), 0, 0);
}

ComPtr<ID3D11Buffer> Renderer::CreateVertexBuffer(const std::vector<Vertex>& vertices)
{
	D3D11_BUFFER_DESC vertexBufferDescription;
	ZeroMemory(&vertexBufferDescription, sizeof(vertexBufferDescription));
	vertexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	vertexBufferDescription.ByteWidth = sizeof(Vertex) * static_cast<unsigned>(vertices.size());
	vertexBufferDescription.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDescription.CPUAccessFlags = 0;
	vertexBufferDescription.MiscFlags = 0;

	ComPtr<ID3D11Buffer> vertexBuffer;
	D3D11_SUBRESOURCE_DATA vertexBufferData;
	ZeroMemory(&vertexBufferData, sizeof(vertexBufferData));
	vertexBufferData.pSysMem = &vertices[0];
	ThrowIfNotOk(
		m_device->CreateBuffer(&vertexBufferDescription, &vertexBufferData, &vertexBuffer),
		"Could not create vertex buffer"
	);

	return vertexBuffer;
}

void Renderer::SetVertexBuffer(ComPtr<ID3D11Buffer> vertexBuffer)
{
	UINT stride = sizeof(Vertex);
	UINT offset = 0;
	m_context->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);
}

void Renderer::SetInputLayout(ComPtr<ID3D11InputLayout> inputLayout)
{
	m_context->IASetInputLayout(inputLayout.Get());
}

void Renderer::SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology)
{
	m_context->IASetPrimitiveTopology(topology);
}

void Renderer::ClearBackBuffer(const Color& color)
{
	m_context->ClearRenderTargetView(m_backBufferRenderTarget.Get(), color);
}

void Renderer::ClearRenderTarget(ComPtr<ID3D11RenderTargetView> renderTarget, const Color& color)
{
	m_context->ClearRenderTargetView(renderTarget.Get(), color);
}

void Renderer::Draw(unsigned vertexCount)
{
	m_context->Draw(vertexCount, 0);
}

void Renderer::Present()
{
	m_swapChain->Present(0, 0);
}
