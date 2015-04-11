#include "stdafx.h"

#include "Avalanche.h"
#include "Game.h"
#include "Utils.h"
#include "ResourceManager.h"

#include "ModelComponent.h"
#include "MyComponents.h"



TestScene::TestScene()
{
	_camera.SetPosition({0.0f, -6.0f, 3.0f});
	_camera.SetViewVector({0.0f, 1.0f, -0.5f});
	_camera.SetUpVector({0.0f, 0.0f, 1.0f});
	_camera.SetPerspective(45.0f, Av::application->GetAspectRatio(), 0.2f, 30.0f);

	Entity *cube1 = CreateCube({-1.5, 0.0f, 0.0f}, 0.035f);
	Entity *cube2 = CreateCube({1.5f, 0.0f, 0.0f}, 0.03f);
	
	MyAnimComponent *canim = new MyAnimComponent();
	cube1->AddComponent(canim);

	MyInputComponent *cinput = new MyInputComponent();
	cinput->speed = 0.5f;
	cube2->AddComponent(cinput);
}

Entity* TestScene::CreateCube(Vector3f pos, float scale)
{
	Entity *cube = entities.CreateEntity();
	TransformComponent *tc = new TransformComponent();
	tc->position = pos;
	tc->rotation = RotationToQuaternion({0,0,1}, 0.0f);
	tc->scale = scale;
	MeshComponent *mesh_comp = new MeshComponent();
	mesh_comp->SetMesh(Av::resourceManager.GetMesh("Cube"));
	MeshDrawComponent *md_comp = new MeshDrawComponent();
	md_comp->material = Av::resourceManager.GetMaterial("Metal");
	cube->AddComponent(tc);
	cube->AddComponent(mesh_comp);
	cube->AddComponent(md_comp);
	return cube;
}

void TestScene::onUpdate(float dt)
{
	_animator.Update(entities, dt);
}

void TestScene::onRender()
{
	Vector3f light_dir(1.0f, 1.0f, -5.0f);
	light_dir.Normalize();

	_render.Clear();
	_render.SetViewMatrix(_camera.GetViewMatrix());
	_render.SetProjectionMatrix(_camera.GetProjectionMatrix());
	_render.AddLight(light_dir);
	_render.Draw(entities);
}