#pragma once

#include "Shaders.h"
#include "ComPtr.h"
#include <string>

struct ID3D11Device;
struct ID3D11PixelShader;

class ShaderCompiler
{
public:
	ShaderCompiler(ComPtr<ID3D11Device> device);

	VertexShader CreateVertexShaderFromPrecompiledFile(const std::string& filename);
	ComPtr<ID3D11PixelShader> CreatePixelShaderFromPrecompiledFile(const std::string& filename);

private:
	ComPtr<ID3D11Device> m_device;
};