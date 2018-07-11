#pragma once

#include <vector>
#include "Types.h"
#include <d3d11.h>
#include "ComPtr.h"
#include "Renderer.h"

class Mesh
{
public:
	Mesh(Renderer& renderer, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices);

	void SetBuffers();
	unsigned long GetNumberOfIndices() const;

private:
	unsigned long m_numberOfIndices;

	Renderer& m_renderer;
	ComPtr<ID3D11Buffer> m_vertexBuffer;
	ComPtr<ID3D11Buffer> m_indexBuffer;
};