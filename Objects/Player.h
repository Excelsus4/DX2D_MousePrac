#pragma once
#include "Viewer/IFollowing.h"

class Player : public IFollowing {
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;

	Sprite* GetSprite();

private:
	float moveSpeed;
	Animation* animation;

	D3DXVECTOR2 focusOffset;
};