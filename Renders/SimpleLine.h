#pragma once
#include "ILineVertex.h"

class SimpleLine {
public:
	SimpleLine(wstring shaderFile, vector<ILineVertex*>* markerVertex);
	virtual ~SimpleLine();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();

	void MapVertex();

private:
	struct Vertex {
		D3DXVECTOR3 Position;
	};

private:
	static const int VERTEX_MAX = 128;
	Vertex vertices[VERTEX_MAX];

private:
	vector<ILineVertex*>* markerVertex;

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX world;
};