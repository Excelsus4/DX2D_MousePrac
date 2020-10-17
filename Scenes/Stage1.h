#pragma once
#include "Scene.h"

class Stage1 : public Scene {
public:
	Stage1(SceneValues* values);
	virtual ~Stage1();

	virtual void Update() override;
	virtual void Render() override;

private:
	void RenderBackground();

private:
	Sprite* backgrounds[3];

	class Player* player;
	class Bullet* bullet;
	class Fire* fire;
};