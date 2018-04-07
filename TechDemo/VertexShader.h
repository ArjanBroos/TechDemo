#pragma once

#include "ComPtr.h"
#include <d3d11.h>

struct VertexShader
{
	ComPtr<ID3D11VertexShader> shader;
	ComPtr<ID3D11InputLayout> inputLayout;
};