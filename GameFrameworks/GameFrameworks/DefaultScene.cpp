#include "DefaultScene.h"
#include "ObjectManager.h"
#include "Camera.h"
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
		if (!Scene::Init(core))
		{
			return false;
		}

		auto cam = GetObjectManager()->CreateCamera();
		cam->GetComponent<Camera>()->SetClearColor(D3DCOLOR_ARGB(255, 255, 0, 255));
		AddChild(cam);

		return true;
	}

	void DefaultScene::Update(const float& dt)
	{
		Scene::Update(dt);

	}

	void DefaultScene::LateUpdate()
	{
		Scene::LateUpdate();

	}

	void DefaultScene::Render()
	{
		Scene::Render();

	}

}