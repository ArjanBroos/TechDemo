#include "Mesh.h"

Mesh::Mesh(Renderer& renderer, const std::vector<Vertex>& vertices, const std::vector<DWORD>& indices) :
	m_numberOfIndices(static_cast<unsigned long>(indices.size())),
	m_renderer(renderer)
{
	m_vertexBuffer = renderer.CreateVertexBuffer(vertices);
	m_indexBuffer = renderer.CreateIndexBuffer(indices);
}

void Mesh::SetBuffers()
{
	m_renderer.SetVertexBuffer(m_vertexBuffer);
	m_renderer.SetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	m_renderer.SetIndexBuffer(m_indexBuffer);
}

unsigned long Mesh::GetNumberOfIndices() const
{
	return m_numberOfIndices;
}
