#include "stdafx.h"
#include "./Systems/Device.h"
#include "./Scenes/Scene.h"
#include "./Viewer/Freedom.h"

#include "./Scenes/Stage1.h"
#include "./Scenes/Stage2.h"
#include "./Scenes/Sonic.h"

SceneValues* values;
vector<Scene*> scenes;

void InitScene() {
	values = new SceneValues();
	values->MainCamera = new Freedom();
	D3DXMatrixIdentity(&values->Projection);

	scenes.push_back(new Sonic(values));
}

void DestroyScene(){
	for (auto scene : scenes)
		SAFE_DELETE(scene);

	SAFE_DELETE(values->MainCamera);
	SAFE_DELETE(values);
}

D3DXVECTOR2 horizontal(0, 800), vertical(0, 600);
void Update() {
	values->MainCamera->Update();

	/*horizontal.x = (float)Width*-0.5f;
	horizontal.y = (float)Width* 0.5f;
	vertical.x = (float)Height*-0.5f;
	vertical.y = (float)Height* 0.5f;*/

	D3DXMatrixOrthoOffCenterLH(&values->Projection, horizontal.x, horizontal.y, vertical.x, vertical.y, -10, 10);

	D3DXMatrixOrthoOffCenterLH(
		&values->Projection,
		(float)Width * -0.5f,
		(float)Width * 0.5f,
		(float)Height * -0.5f,
		(float)Height * 0.5f,
		-10, 10
	);

	for (auto scene : scenes)
		scene->Update();
}

void Render() {
	D3DXCOLOR bgColor = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1);
	DeviceContext->ClearRenderTargetView(RTV, (float*)bgColor);
	{
		//ImGui::SliderFloat2("Horizontal", (float*)&horizontal, -1000, 1000);
		//ImGui::SliderFloat2("Vertical", (float*)&vertical, -1000, 1000);

		// ImGui::LabelText("FPS", "%.0f", ImGui::GetIO().Framerate);
		for (auto scene : scenes)
			scene->Render();
	}
	ImGui::Render();

	DirectWrite::GetDC()->BeginDraw();
	{
		wstring text = L"";

		RECT rect;
		rect.left = 20;
		rect.top = 0;
		rect.right = 600;
		rect.bottom = 20;

		text = L"Frame Per Second : " + to_wstring((int)ImGui::GetIO().Framerate);
		DirectWrite::RenderText(text, rect);

		rect.top += 20;
		rect.bottom += 20;

		text = L"Camera Position : ";
		text += to_wstring((int)values->MainCamera->Position().x);
		text += L", ";
		text += to_wstring((int)values->MainCamera->Position().y);
		DirectWrite::RenderText(text, rect);
	}

	DirectWrite::GetDC()->EndDraw();
	SwapChain->Present(0, 0);
}

