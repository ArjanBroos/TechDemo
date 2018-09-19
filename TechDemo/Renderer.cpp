#include "Renderer.h"
#include <d3d11.h>
#include "Utility.h"
#include "Color.h"
#include "Vertex.h"

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
		"Could not create Direct3D11 device and swap chain."
	);

	ThrowIfNotOk(
		m_swapChain->ResizeBuffers(1, windowWidth, windowHeight, DXGI_FORMAT_R8G8B8A8_UNORM, NULL),
		"Could not resize buffers."
	);

	ComPtr<ID3D11Texture2D> backBuffer;
	ThrowIfNotOk(
		m_swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), &backBuffer),
		"Could not retrieve buffer from swap chain."
	);

	D3D11_TEXTURE2D_DESC depthStencilDescription;
	depthStencilDescription.Width = windowWidth;
	depthStencilDescription.Height = windowHeight;
	depthStencilDescription.MipLevels = 1;
	depthStencilDescription.ArraySize = 1;
	depthStencilDescription.Format = DXGI_FORMAT_D24_UNORM_S8_UINT;
	depthStencilDescription.SampleDesc.Count = 1;
	depthStencilDescription.SampleDesc.Quality = 0;
	depthStencilDescription.Usage = D3D11_USAGE_DEFAULT;
	depthStencilDescription.BindFlags = D3D11_BIND_DEPTH_STENCIL;
	depthStencilDescription.CPUAccessFlags = 0;
	depthStencilDescription.MiscFlags = 0;

	ComPtr<ID3D11Texture2D> depthStencilBuffer;
	ThrowIfNotOk(
		m_device->CreateTexture2D(&depthStencilDescription, NULL, depthStencilBuffer.GetAddressOf()),
		"Could not create depth stencil buffer."
	);

	ThrowIfNotOk(
		m_device->CreateDepthStencilView(depthStencilBuffer.Get(), NULL, m_depthStencilView.GetAddressOf()),
		"Could not create depth stencil view."
	);

	ThrowIfNotOk(
		m_device->CreateRenderTargetView(backBuffer.Get(), NULL, &m_backBufferRenderTarget),
		"Could not create render target."
	);

	D3D11_VIEWPORT viewport;
	viewport.TopLeftX = 0;
	viewport.TopLeftY = 0;
	viewport.Width = static_cast<float>(windowWidth);
	viewport.Height = static_cast<float>(windowHeight);
	viewport.MinDepth = 0.f;
	viewport.MaxDepth = 1.f;

	m_context->RSSetViewports(1, &viewport);
}

ComPtr<ID3D11Device> Renderer::GetDevice()
{
	return m_device;
}

void Renderer::SetRenderTarget(ComPtr<ID3D11RenderTargetView> renderTarget)
{
	m_context->OMSetRenderTargets(1, renderTarget.GetAddressOf(), m_depthStencilView.Get());
}

void Renderer::SetRenderTargetToBackBuffer()
{
	SetRenderTarget(m_backBufferRenderTarget);
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

ComPtr<ID3D11Buffer> Renderer::CreateIndexBuffer(const std::vector<DWORD>& indices)
{
	D3D11_BUFFER_DESC indexBufferDescription;
	ZeroMemory(&indexBufferDescription, sizeof(indexBufferDescription));
	indexBufferDescription.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDescription.ByteWidth = sizeof(DWORD) * static_cast<unsigned>(indices.size());
	indexBufferDescription.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDescription.CPUAccessFlags = 0;
	indexBufferDescription.MiscFlags = 0;

	ComPtr<ID3D11Buffer> indexBuffer;
	D3D11_SUBRESOURCE_DATA indexBufferData;
	ZeroMemory(&indexBufferData, sizeof(indexBufferData));
	indexBufferData.pSysMem = &indices[0];
	ThrowIfNotOk(
		m_device->CreateBuffer(&indexBufferDescription, &indexBufferData, &indexBuffer),
		"Could not create index buffer"
	);

	return indexBuffer;
}

void Renderer::SetIndexBuffer(ComPtr<ID3D11Buffer> indexBuffer)
{
	m_context->IASetIndexBuffer(indexBuffer.Get(), DXGI_FORMAT_R32_UINT, 0);
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

void Renderer::ClearDepthStencilView()
{
	m_context->ClearDepthStencilView(m_depthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.f, 0);
}

void Renderer::Draw(unsigned indexCount)
{
	m_context->DrawIndexed(indexCount, 0, 0);
}

void Renderer::Present()
{
	m_swapChain->Present(0, 0);
}
