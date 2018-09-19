#pragma once

#include <vector>
#include "ComPtr.h"

class Renderer;
struct Vertex;
struct ID3D11Buffer;

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