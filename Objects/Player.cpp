#include "stdafx.h"
#include "Player.h"
#include "Renders/ILineVertex.h"

Player::Player(D3DXVECTOR2 position, D3DXVECTOR2 scale) :
	moveSpeed(200.0f), focusOffset(-180, -120), singleLine(Shaders + L"015_Bounding.fx", &vertical)
	, vertical(position, position), gravity(-98.1f), velocity(0, 0), onGround(0)
{
	animation = new Animation();

	wstring spriteFile = Textures + L"Metalslug.png";
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	Clip* clip;
	// Idle
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 4, 2, 33, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 35, 2, 64, 40), 0.3f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 64, 2, 93, 40), 0.3f);
		animation->AddClip(clip);
	}

	// Run
	{
		clip = new Clip(PlayMode::Loop);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 0, 600, 32, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 33, 600, 64, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 65, 600, 96, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 97, 600, 124, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 125, 600, 154, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 158, 600, 188, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 191, 600, 222, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 224, 600, 258, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 259, 600, 294, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 295, 600, 326, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 329, 600, 360, 640), 0.1f);
		clip->AddFrame(new Sprite(spriteFile, shaderFile, 362, 600, 393, 640), 0.1f);
		animation->AddClip(clip);
	}

	Position(100, 170);
	animation->Scale(scale);
	animation->Play(0);

	animation->DrawBound(true);
}

Player::~Player()
{
	SAFE_DELETE(animation);
}

void Player::FixedUpdate(vector<ILineVertex*>* markers)
{
	D3DXVECTOR2 position = animation->Position();

	bool bMove = false;

	if (Key->Press('A')) {
		bMove = true;
		position.x -= moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 180, 0);
	}
	else if (Key->Press('D')) {
		bMove = true;
		position.x += moveSpeed * Timer->Elapsed();
		animation->RotationDegree(0, 0, 0);
	}

	if (!onGround) {
		// On Air
		velocity.y += gravity * Timer->Elapsed();
		position += velocity * Timer->Elapsed();
		vertical = Line::DoubleVector2(position, position + D3DXVECTOR2(0, -20));

		//Line Collision
		for (int i = 0; i + 1 < markers->size(); i += 2) {
			D3DXVECTOR2 res;
			if (LineCollision((*markers)[i]->Position(), (*markers)[i + 1]->Position(),res)) {
				onGround = true;
				position = res - D3DXVECTOR2(0, -20);
			}
		}
	}
	else {
		// On Ground
		velocity.y += 0;
		vertical = Line::DoubleVector2(position, position + D3DXVECTOR2(0, -20));
		onGround = false;
		for (int i = 0; i + 1 < markers->size(); i += 2) {
			D3DXVECTOR2 res;
			if (LineCollision((*markers)[i]->Position(), (*markers)[i + 1]->Position(),res)) {
				onGround = true;
				position = res - D3DXVECTOR2(0, -20);
			}
		}
	}

	Position(position);
	animation->Play(bMove ? 1 : 0);
}

void Player::Update(D3DXMATRIX & V, D3DXMATRIX & P)
{
	animation->Update(V, P);
	singleLine.Update(V, P);
}

void Player::Render()
{
	ImGui::SliderFloat("MoveSpeed", &moveSpeed, 50, 400);

	animation->Render();
	singleLine.Render();
}

void Player::Focus(D3DXVECTOR2 * position, D3DXVECTOR2 * size)
{
	*position = animation->Position() - focusOffset;
	/*D3DXVECTOR2 textureSize = animation->TextureSize();
	D3DXVECTOR2 scale = animation->Scale();

	(*size).x = textureSize.x*scale.x;
	(*size).y = textureSize.y*scale.y;*/
	(*size) = D3DXVECTOR2(1, 1);
}

bool Player::LineCollision(D3DXVECTOR2 p1, D3DXVECTOR2 p2, D3DXVECTOR2& result)
{
	return LineCollision(Line::DoubleVector2(p1, p2), result);
}

bool Player::LineCollision(Line::DoubleVector2 dvec, D3DXVECTOR2& result)
{
	return Line::LineCollision(dvec, vertical, result);
}

void Player::Position(D3DXVECTOR2 vec)
{
	vertical = Line::DoubleVector2(vec, vec + D3DXVECTOR2(0, -20));
	singleLine.MapVertex();
	animation->Position(vec);
}

Sprite * Player::GetSprite()
{
	return animation->GetSprite();
}
