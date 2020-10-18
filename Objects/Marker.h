#pragma once
#include "Renders/ILineVertex.h"

class Marker : public ILineVertex{
public:
	Marker(wstring shaderFile, D3DXVECTOR2 start);
	virtual ~Marker();

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) override;
	virtual void Render() override;

	Clip* GetClip() { return clip; }
	virtual D3DXVECTOR2 Position() const override { return position; }
	virtual void Position(D3DXVECTOR2 vec) override;

	virtual void isSelected(bool s) override;
	virtual bool isSelected() const override;
private:
	Clip* clip;

	D3DXVECTOR2 position;
	D3DXVECTOR2 scale;
	D3DXVECTOR3 rotation;

	bool isS;
};