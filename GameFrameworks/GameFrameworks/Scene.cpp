#include "Scene.h"

namespace meltshine
{
	Scene::Scene()
	{
	}

	Scene::~Scene()
	{
	}

	bool Scene::Init(std::shared_ptr<Core> core)
	{
		if (!GameObject::Init(core))
		{
			return false;
		}

		// TODO: 기본 카메라 게임 오브젝트를 생성해 자식으로 추가합니다.

		return true;
	}

}