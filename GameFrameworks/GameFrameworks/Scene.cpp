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

		// TODO: �⺻ ī�޶� ���� ������Ʈ�� ������ �ڽ����� �߰��մϴ�.

		return true;
	}

}