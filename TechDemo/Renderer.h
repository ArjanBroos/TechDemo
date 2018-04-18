#pragma once

#include "ComPtr.h"
#include <d3d11.h>
#include <string>
#include "Types.h"
#include "VertexShader.h"
#include <vector>

class Renderer
{
public:
	Renderer(unsigned windowWidth, unsigned windowHeight, HWND windowHandle);

	void SetRenderTarget(ComPtr<ID3D11RenderTargetView> renderTarget);
	void SetRenderTargetToBackBuffer();

	VertexShader CreateVertexShaderFromPrecompiledFile(const std::string& filename);
	ComPtr<ID3D11PixelShader> CreatePixelShaderFromPrecompiledFile(const std::string& filename);
	void SetVertexShader(ComPtr<ID3D11VertexShader> vertexShader);
	void SetPixelShader(ComPtr<ID3D11PixelShader> pixelShader);

	ComPtr<ID3D11Buffer> CreateVertexBuffer(const std::vector<Vertex>& vertices);
	void SetVertexBuffer(ComPtr<ID3D11Buffer> vertexBuffer);

	ComPtr<ID3D11Buffer> CreateIndexBuffer(const std::vector<DWORD>& indices);
	void SetIndexBuffer(ComPtr<ID3D11Buffer> indexBuffer);

	void SetInputLayout(ComPtr<ID3D11InputLayout> inputLayout);

	void SetPrimitiveTopology(D3D_PRIMITIVE_TOPOLOGY topology);

	void ClearBackBuffer(const Color& color);
	void ClearRenderTarget(ComPtr<ID3D11RenderTargetView> renderTarget, const Color& color);

	void Draw(unsigned indexCount);
	void Present();

private:
	ComPtr<ID3D11RenderTargetView> m_backBufferRenderTarget;
	ComPtr<IDXGISwapChain> m_swapChain;
	ComPtr<ID3D11Device> m_device;
	ComPtr<ID3D11DeviceContext> m_context;
};