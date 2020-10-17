#include "stdafx.h"
#include "Stage2.h"
#include "Objects/Player.h"
#include "Viewer/Following.h"

Stage2::Stage2(SceneValues * values):
	Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";

	backgrounds = new Sprite(Textures + L"Stage.png", shaderFile);
	backgrounds->Scale(2.5f, 2.5f);
	backgrounds->Position(0, 300);

	player = new Player(D3DXVECTOR2(130, 140), D3DXVECTOR2(2.5f, 2.5f));

	SAFE_DELETE(values->MainCamera);
	values->MainCamera = new Following(player);
}

Stage2::~Stage2()
{
	SAFE_DELETE(player);
	SAFE_DELETE(backgrounds);
}

void Stage2::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backgrounds->Update(V, P);

	player->Update(V, P);
}

void Stage2::Render()
{
	backgrounds->Render();
	player->Render();
}
