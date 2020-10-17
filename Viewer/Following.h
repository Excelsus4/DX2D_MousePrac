#pragma once
#include "IFollowing.h"
#include "Camera.h"

class Following : public Camera{
public:
	Following(IFollowing* focus = NULL);
	virtual ~Following();

	void Change(IFollowing* focus);
	virtual void Update() override;

private:
	IFollowing* focus;
};