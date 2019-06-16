#include "DefaultScene.h"

namespace meltshine
{
	DefaultScene::DefaultScene()
	{
	}

	DefaultScene::~DefaultScene()
	{
	}

	bool DefaultScene::Init(std::shared_ptr<Core> core)
	{
		return Scene::Init(core);
	}

	void DefaultScene::Update(const float& dt)
	{
		Scene::Update(dt);

	}

	void DefaultScene::LateUpdate()
	{
		Scene::LateUpdate();

	}

	void DefaultScene::PreRender()
	{
		Scene::PreRender();

	}

	void DefaultScene::Render()
	{
		Scene::Render();

	}

	void DefaultScene::PostRender()
	{
		Scene::PostRender();

	}

	void DefaultScene::RenderImage()
	{
		Scene::RenderImage();

	}

}