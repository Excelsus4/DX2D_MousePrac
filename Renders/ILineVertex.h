#pragma once
#include "stdafx.h"

class ILineVertex {
public:
	virtual D3DXVECTOR2 Position() const = 0;
	virtual void Position(D3DXVECTOR2 vec) = 0;

	virtual void Update(D3DXMATRIX& V, D3DXMATRIX& P) = 0;
	virtual void Render() = 0;

	virtual void isSelected(bool s) = 0;
	virtual bool isSelected() const = 0;
};