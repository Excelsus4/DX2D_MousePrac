#include "stdafx.h"
#include "Stage1.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"
#include "Objects/Bullet.h"
#include "Objects/Fire.h"

Stage1::Stage1(SceneValues * values) :
	Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	backgrounds[0] = new Sprite(Textures + L"Stage2.png", shaderFile, 26, 311, 613, 503);
	backgrounds[0]->Position(400, 350);
	backgrounds[0]->Scale(1.2f, 2.6f);

	backgrounds[1] = new Sprite(Textures + L"Stage2.png", shaderFile, 13, 11, 714, 215);
	backgrounds[1]->Position(400, 350);
	backgrounds[1]->Scale(1.2f, 2.6f);

	backgrounds[2] = new Sprite(Textures + L"Stage2.png", shaderFile, 13, 242, 894, 279);
	backgrounds[2]->Position(400, 40);
	backgrounds[2]->Scale(1.2f, 2.6f);

	player = new Player(D3DXVECTOR2(130, 100), D3DXVECTOR2(2.5f, 2.5f));
	bullet = new Bullet(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 300), 0, 0);
	fire = new Fire(Shaders + L"009_Sprite.fx", D3DXVECTOR2(300, 100));
}

Stage1::~Stage1()
{
	SAFE_DELETE(fire);
	SAFE_DELETE(player);
	SAFE_DELETE(bullet);

	SAFE_DELETE(backgrounds[2]);
	SAFE_DELETE(backgrounds[1]);
	SAFE_DELETE(backgrounds[0]);
}

void Stage1::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backgrounds[0]->Update(V, P);
	backgrounds[1]->Update(V, P);
	backgrounds[2]->Update(V, P);

	player->Update(V, P);
	bullet->Update(V, P);
	fire->Update(V, P);
}

void Stage1::Render()
{
	RenderBackground();

	static bool check = false;
	Sprite* a = player->GetSprite();
	Sprite* b = fire->GetClip()->GetSprite();

	check = Sprite::Obb(a, b);

	a->DrawCollision(check);
	b->DrawCollision(check);
	ImGui::LabelText("OBB", "%d", check ? 1 : 0);

	player->Render();
	bullet->Render();
	fire->Render();
}

void Stage1::RenderBackground()
{
	backgrounds[0]->Render();
	backgrounds[1]->Render();
	backgrounds[2]->Render();
}
