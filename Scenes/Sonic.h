#pragma once
#include "Scene.h"

class Sonic :public Scene {
public:
	Sonic(SceneValues* values);
	virtual ~Sonic();

	void Update() override;
	void Render() override;

private:
	Sprite* backGround;

	class Player* player;
	vector<class ILineVertex*> markers;
	class ILineVertex* selected;
	D3DXVECTOR2 selectedPrevPos;
	bool dragging;

	class SimpleLine* lineRender;
};
