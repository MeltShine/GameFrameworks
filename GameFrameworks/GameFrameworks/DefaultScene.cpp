#include "DefaultScene.h"
#include "ObjectManager.h"
#include "Camera.h"
#include "Core.h"
#include "TestCode.h"
#include "InputHandler.h"
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
		cam->GetComponent<Camera>()->SetClearFlags(D3DCLEAR_ZBUFFER | D3DCLEAR_STENCIL);
		AddChild(cam);
		AddComponent(GetObjectManager()->CreateComponent<TestCode>());
		return true;
	}

	void DefaultScene::Update(const float& dt)
	{
		Scene::Update(dt);


		if (GetInputHandler()->GetKeyPress(VK_ESCAPE))
		{
			PostQuitMessage(0);
		}
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