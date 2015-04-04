#pragma once

#include "GameApp.h"
#include "Camera.h"
#include "Model.h"

class TestScene : public IScene
{
	Camera _camera;

	Model *_model;

	Vector3f meshPos;
	float meshAngle = 0.0f;

	void SetupGL();

public:
	TestScene();
	~TestScene();

	virtual void onRender() override;
	virtual void onUpdate(float dt) override;
	virtual void onKeyDown(int key) override;
	//virtual void onMouseDown(int key) override;
	//virtual void onMouseUp(int key) override;
};