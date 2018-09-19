#include "ShaderCompiler.h"
#include "Utility.h"
#include <d3d11.h>

ShaderCompiler::ShaderCompiler(ComPtr<ID3D11Device> device) :
	m_device(device)
{
}

VertexShader ShaderCompiler::CreateVertexShaderFromPrecompiledFile(const std::string& filename)
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

ComPtr<ID3D11PixelShader> ShaderCompiler::CreatePixelShaderFromPrecompiledFile(const std::string& filename)
{
	auto pixelShaderByteCode = ReadByteArray(filename);
	ComPtr<ID3D11PixelShader> pixelShader;
	ThrowIfNotOk(
		m_device->CreatePixelShader(&pixelShaderByteCode[0], pixelShaderByteCode.size(), NULL, &pixelShader),
		"Could not create pixel shader"
	);
	return pixelShader;
}
