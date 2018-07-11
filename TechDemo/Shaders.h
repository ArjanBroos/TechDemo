#pragma once

#include "ComPtr.h"
#include <d3d11.h>

struct VertexShader
{
	ComPtr<ID3D11VertexShader> shader;
	ComPtr<ID3D11InputLayout> inputLayout;
};

struct Shaders
{
	Shaders() = default;
	Shaders(const VertexShader& vertexShader, ComPtr<ID3D11PixelShader> pixelShader) :
		vertexShader(vertexShader.shader), inputLayout(vertexShader.inputLayout), pixelShader(pixelShader) {}
	Shaders(ComPtr<ID3D11VertexShader> vertexShader, ComPtr<ID3D11InputLayout> inputLayout, ComPtr<ID3D11PixelShader> pixelShader) :
		vertexShader(vertexShader), inputLayout(inputLayout), pixelShader(pixelShader) {}

	ComPtr<ID3D11VertexShader> vertexShader;
	ComPtr<ID3D11InputLayout> inputLayout;
	ComPtr<ID3D11PixelShader> pixelShader;
};