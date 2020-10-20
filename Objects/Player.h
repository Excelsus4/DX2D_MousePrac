#pragma once
#include "Viewer/IFollowing.h"
#include "Renders/SingleLine.h"

class Player : public IFollowing {
public:
	Player(D3DXVECTOR2 position, D3DXVECTOR2 scale);
	~Player();

	void FixedUpdate(vector<class ILineVertex*>* markers);
	void Update(D3DXMATRIX& V, D3DXMATRIX& P);
	void Render();

	virtual void Focus(D3DXVECTOR2* position, D3DXVECTOR2* size) override;
	bool LineCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2& result);
	bool LineCollision(Line::DoubleVector2 dvec, D3DXVECTOR2& result);

	void Position(float x, float y) { Position(D3DXVECTOR2(x, y)); }
	void Position(D3DXVECTOR2 vec);

	Sprite* GetSprite();

private:
	bool onGround;
	D3DXVECTOR2 velocity;
	float gravity;

	float moveSpeed;
	Animation* animation;

	D3DXVECTOR2 focusOffset;

	Line::DoubleVector2 vertical;
	SingleLine singleLine;
};