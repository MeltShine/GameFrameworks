#include "ObjectManager.h"

// 게임 오브젝트
#include "GameObject.h"
#include "Scene.h"

// 컴포넌트
#include "Component.h"
#include "Camera.h"

namespace meltshine
{
	ObjectManager::ObjectManager()
	{
	}

	ObjectManager::~ObjectManager()
	{
	}

	bool ObjectManager::Init(std::shared_ptr<Core> core)
	{
		if (core == nullptr)
		{
			return false;
		}
		_core = core;
		return true;
	}

	std::shared_ptr<GameObject> ObjectManager::CreateEmptyObject()
	{
		std::shared_ptr<GameObject> obj(new GameObject);
		if (obj && obj->Init(_core.lock()))
		{
			obj->SetName("Empty Object");
			return obj;
		}
		return nullptr;
	}

	std::shared_ptr<GameObject> ObjectManager::CreateCamera()
	{
		std::shared_ptr<GameObject> obj(new GameObject);
		std::shared_ptr<Camera> cam = CreateComponent<Camera>();
		if (obj && cam && obj->Init(_core.lock()))
		{
			obj->SetName("Camera");
			obj->AddComponent(cam);
			return obj;
		}
		return nullptr;
	}

	std::shared_ptr<Scene> ObjectManager::CreateEmptyScene()
	{
		auto scene = std::shared_ptr<Scene>(new Scene);
		if (scene && scene->Init(_core.lock()))
		{
			return scene;
		}
		return nullptr;
	}

	void ObjectManager::InsertOrigin(std::string key, std::shared_ptr<GameObject> obj)
	{
		if (HasOrigin(key) || obj == nullptr)
		{
			return;
		}

		_origin_objects.emplace(key, obj);
	}

	void ObjectManager::RemoveOrigin(const std::string& key)
	{
		_origin_objects.erase(key);
	}

	void ObjectManager::RemoveAllOrigin()
	{
		_origin_objects.clear();
	}

	bool ObjectManager::HasOrigin(const std::string& key)
	{
		return (_origin_objects.find(key) != _origin_objects.end());
	}

	std::shared_ptr<GameObject> ObjectManager::GetOrigin(const std::string& key)
	{
		return _origin_objects.at(key);
	}

}