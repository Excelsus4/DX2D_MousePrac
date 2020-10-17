#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Objects/Marker.h"
#include "Viewer/Freedom.h"

Sonic::Sonic(SceneValues * values): Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	
	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	player = new Player(D3DXVECTOR2(130, 140), D3DXVECTOR2(2.5f, 2.5f));

	((Freedom*)(values->MainCamera))->Position(0, 0);

}

Sonic::~Sonic()
{
	for (Marker* marker : markers)
		SAFE_DELETE(marker);

	SAFE_DELETE(player);
	SAFE_DELETE(backGround);
}

void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);
	player->Update(V, P);

	if (Mouse->DoubleClick(0))
	{
		D3DXVECTOR2 mouse = Mouse->Position();
		mouse.x = mouse.x - (float)Width*0.5f;
		mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;
		D3DXVECTOR2 camera = values->MainCamera->Position();
		D3DXVECTOR2 position = mouse + camera;

		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", position));
	}
	
	for (Marker* marker : markers)
		marker->Update(V, P);
}

void Sonic::Render()
{
	ImGui::LabelText("Position", "%.0f, %.0f", Mouse->Position().x, Mouse->Position().y);
	ImGui::LabelText("Left Down", "%d", Mouse->Down(0) ? 1 : 0);
	ImGui::LabelText("Left Up", "%d", Mouse->Up(0) ? 1 : 0);
	ImGui::LabelText("Left Press", "%d", Mouse->Press(0) ? 1 : 0);
	ImGui::LabelText("Left Doubleclick", "%d", Mouse->DoubleClick(0) ? 1 : 0);

	ImGui::LabelText("Wheel", "%d", Mouse->Wheel());

	backGround->Render();
	//player->Render();

	for (Marker* marker : markers)
		marker->Render();
}
