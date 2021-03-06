#include "stdafx.h"
#include "Sonic.h"
#include "Objects/Player.h"
#include "Objects/Marker.h"
#include "Viewer/Freedom.h"
#include "Renders/SimpleLine.h"

Sonic::Sonic(SceneValues * values): Scene(values)
{
	wstring shaderFile = Shaders + L"009_Sprite.fx";
	
	backGround = new Sprite(Textures + L"Sonic.png", shaderFile);
	backGround->Position(0, 0);

	player = new Player(D3DXVECTOR2(130, 140), D3DXVECTOR2(1, 1));

	((Freedom*)(values->MainCamera))->Position(0, 0);

	markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2(-380, -280)));
	markers.push_back(new Marker(Shaders + L"009_Sprite.fx", D3DXVECTOR2( 380, -280)));

	wstring lineShader = Shaders + L"015_Bounding.fx";
	lineRender = new SimpleLine(lineShader, &markers);
	selected = nullptr;
	dragging = false;

	lineRender->MapVertex();
}

Sonic::~Sonic()
{
	for (ILineVertex* marker : markers)
		SAFE_DELETE(marker);

	SAFE_DELETE(player);
	SAFE_DELETE(backGround);
	SAFE_DELETE(lineRender);
}

void Sonic::Update()
{
	D3DXMATRIX V = values->MainCamera->View();
	D3DXMATRIX P = values->Projection;

	backGround->Update(V, P);
	player->FixedUpdate(&markers);

	if (Mouse->Down(0)) {
		// if selection is on and its near the selected point, then start drag...
		// else, then try to select nearest point.
		ILineVertex* prev = selected;
		selected = nullptr;
		for (auto a : markers) {
			D3DXVECTOR2 mouse = Mouse->Position();
			mouse.x = mouse.x - (float)Width*0.5f;
			mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;

			if (((Marker*)a)->GetClip()->GetSprite()->AABB(mouse)) {
				if (selected != nullptr)
					selected->isSelected(false);
				a->isSelected(true);
				selected = a;
				selectedPrevPos = mouse;
				dragging = true;
			}
			else {
				a->isSelected(false);
			}
		}
	}
	else if (Mouse->Press(0)) {
		// if dragging is on, then update the drag
		if (dragging) {
			D3DXVECTOR2 mouse = Mouse->Position();
			mouse.x = mouse.x - (float)Width*0.5f;
			mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;

			D3DXVECTOR2 delta = mouse - selectedPrevPos;
			selectedPrevPos = mouse;

			selected->Position(selected->Position() + delta);
			lineRender->MapVertex();
		}

	}
	else if (Mouse->Up(0)) {
		// if dragging is on, then release the drag
		if (dragging)
			dragging = false;
	}

	if (Mouse->DoubleClick(0))
	{
		// Only active when selection is not on...
		D3DXVECTOR2 mouse = Mouse->Position();
		mouse.x = mouse.x - (float)Width*0.5f;
		mouse.y = (mouse.y - (float)Height*0.5f)*-1.0f;
		D3DXVECTOR2 camera = values->MainCamera->Position();
		D3DXVECTOR2 position = mouse + camera;

		markers.push_back(new Marker(Shaders + L"009_Sprite.fx", position));
		lineRender->MapVertex();
	}
	
	for (ILineVertex* marker : markers)
		marker->Update(V, P);

	lineRender->Update(V, P);
	player->Update(V, P);
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

	for (ILineVertex* marker : markers)
		marker->Render();

	lineRender->Render();

	player->Render();
}
