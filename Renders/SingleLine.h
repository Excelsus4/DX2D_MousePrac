#pragma once

class SingleLine {
public:
	SingleLine(wstring shaderFile, Line::DoubleVector2* line);
	virtual ~SingleLine();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	virtual void Render();

	void MapVertex();
private:
	struct Vertex {
		D3DXVECTOR3 Position;
	};
	
private:
	static const int VERTEX_MAX = 2;
	Vertex vertices[VERTEX_MAX];

private:
	Line::DoubleVector2* markerVertex;

	Shader* shader;
	ID3D11Buffer* vertexBuffer;

	D3DXMATRIX world;
};