#pragma once
#include "Scene.h"

class Stage2 : public Scene {
public:
	Stage2(SceneValues* values);
	virtual ~Stage2();

	virtual void Update() override;
	virtual void Render() override;

private:
	Sprite* backgrounds;

	class Player* player;
};