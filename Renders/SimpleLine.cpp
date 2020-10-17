#include "stdafx.h"
#include "SimpleLine.h"

SimpleLine::SimpleLine(wstring shaderFile, vector<ILineVertex*>* markerVertex)
	:markerVertex(markerVertex)
{
	shader = new Shader(shaderFile);

	for (int i = 0; i < VERTEX_MAX; i++) {
		vertices[i].Position = D3DXVECTOR3(-3080, -3080, -3080);
	}

	//Create Vertext Buffer
	{
		D3D11_BUFFER_DESC desc = { 0 };
		desc.Usage = D3D11_USAGE_DYNAMIC;
		desc.ByteWidth = sizeof(Vertex) * VERTEX_MAX;
		desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
		desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

		D3D11_SUBRESOURCE_DATA data = { 0 };
		data.pSysMem = vertices;

		HRESULT hr = Device->CreateBuffer(&desc, &data, &vertexBuffer);
		assert(SUCCEEDED(hr));
	}

	D3DXMatrixIdentity(&world);
}

SimpleLine::~SimpleLine()
{
}

void SimpleLine::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	shader->AsMatrix("View")->SetMatrix(V);
	shader->AsMatrix("Projection")->SetMatrix(P);
	shader->AsMatrix("World")->SetMatrix(world);
}

void SimpleLine::Render()
{
	ImGui::LabelText("Marker Size", "%d", markerVertex->size());

	UINT stride = sizeof(Vertex);
	UINT offset = 0;

	DeviceContext->IASetVertexBuffers(0, 1, &vertexBuffer, &stride, &offset);
	DeviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_LINELIST);

	shader->Draw(0, 0, markerVertex->size());
}

void SimpleLine::MapVertex()
{
	D3D11_MAPPED_SUBRESOURCE mappedResource;
	ZeroMemory(&mappedResource, sizeof(D3D11_MAPPED_SUBRESOURCE));

	for (int i = 0; i < markerVertex->size(); i++) {
		D3DXVECTOR2 temp = (*markerVertex)[i]->Position();
		vertices[i].Position = D3DXVECTOR3(temp.x, temp.y, 0.0f);
	}

	//  Disable GPU access to the vertex buffer data.
	DeviceContext->Map(vertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedResource);
	//  Update the vertex buffer here.
	memcpy(mappedResource.pData, vertices, sizeof(vertices));
	//  Reenable GPU access to the vertex buffer data.
	DeviceContext->Unmap(vertexBuffer, 0);
}
