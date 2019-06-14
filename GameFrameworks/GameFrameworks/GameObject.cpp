#include "GameObject.h"

#include <algorithm>

// Managers
#include "Core.h"
#include "ObjectManager.h"

// Components
#include "Component.h"
#include "Transform.h"

namespace meltshine
{
	GameObject::GameObject()
		: _name()
		, _hash_of_name()
		, _tag()
		, _running(false)
		, _visible(true)
		, _dirty(false)
		, _depth()
	{
	}

	GameObject::~GameObject()
	{
		RemoveAllChildren();
		RemoveAllComponents();
		RemoveChildFromParent();
	}

	bool GameObject::Init(std::shared_ptr<Core> core)
	{
		if (core == nullptr)
		{
			return false;
		}

		SetCore(core);
		SetDirect3D(core->GetDirect3D());
		SetRenderer(core->GetRenderer());
		SetObjectManager(core->GetObjectManager());

		auto transform = GetObjectManager()->CreateComponent<Transform>();
		if (transform == nullptr)
		{
			return false;
		}
		AddComponent(transform);
		return true;
	}

	void GameObject::OnEnter()
	{
		if (!_running)
		{
			return;
		}

		// TODO: SetScene(_scene_ctrl->GetCurrentScene());

		for (auto& component : _components)
		{
			component->OnEnter();
		}

		for (auto& child : _children)
		{
			child->OnEnter();
		}

	}

	void GameObject::OnExit()
	{
		if (!_running)
		{
			return;
		}

		for (auto& component : _components)
		{
			component->OnExit();
		}

		for (auto& child : _children)
		{
			child->OnExit();
		}

	}

	void GameObject::Update(const float& dt)
	{
		if (!_running)
		{
			return;
		}

		SortChildren();

		for (auto& component : _components)
		{
			component->Update(dt);
		}

		for (auto& child : _children)
		{
			child->Update(dt);
		}
	}

	void GameObject::LateUpdate()
	{
		if (!_running)
		{
			return;
		}

		for (auto& component : _components)
		{
			component->LateUpdate();
		}

		for (auto& child : _children)
		{
			child->LateUpdate();
		}
	}

	void GameObject::PreRender()
	{
		// TODO: 이 곳에서 카메라의 그리기 대상으로 해당되는지 확인하는 코드를 작성하세요.
		if (!_running || !_visible)
		{
			return;
		}

		for (auto& component : _components)
		{
			component->PreRender();
		}

		for (auto& child : _children)
		{
			child->PreRender();
		}
	}

	void GameObject::Render()
	{
		// TODO: 이 곳에서 카메라의 그리기 대상으로 해당되는지 확인하는 코드를 작성하세요.
		// GetScene()->GetVisitingCamera()->CheckMaskingTarget(_tag);
		if (!_running || !_visible)
		{
			return;
		}

		for (auto& component : _components)
		{
			component->Render();
		}

		for (auto& child : _children)
		{
			child->Render();
		}
	}

	void GameObject::PostRender()
	{
		// TODO: 이 곳에서 카메라의 그리기 대상으로 해당되는지 확인하는 코드를 작성하세요.
		if (!_running || !_visible)
		{
			return;
		}

		for (auto& component : _components)
		{
			component->PostRender();
		}

		for (auto& child : _children)
		{
			child->PostRender();
		}
	}

	void GameObject::RenderImage()
	{
		// TODO: 이 곳에서 카메라의 그리기 대상으로 해당되는지 확인하는 코드를 작성하세요.
		for (auto& component : _components)
		{
			component->RenderImage();
		}

		for (auto& child : _children)
		{
			child->RenderImage();
		}
	}

	void GameObject::SetName(std::string name)
	{
		if (EqualByName(name))
		{
			return;
		}

		_name = std::move(name);
		_hash_of_name = StrToHash(name);
	}

	void GameObject::AddChild(std::shared_ptr<GameObject> obj)
	{
		if (obj->GetParent() != nullptr)
		{
			return;
		}
		_children.push_back(obj);
		obj->_running = true;
		obj->SetParent(shared_from_this());
		if (_running)
		{
			obj->OnEnter();
		}
		_dirty = true;
	}

	bool GameObject::HasChild(std::shared_ptr<GameObject> obj)
	{
		for (auto& child : _children)
		{
			if (child == obj)
			{
				return true;
			}
		}
		return false;
	}

	void GameObject::RemoveChild(std::shared_ptr<GameObject> obj)
	{
		auto it = _children.begin();
		auto end = _children.end();
		while (it != end)
		{
			auto& child = *it;
			if (child == obj)
			{
				if (_running)
				{
					child->OnExit();
				}
				child->SetParent(nullptr);
				child->_running = false;
				_children.erase(it);
				break;
			}

			++it;
		}
	}

	void GameObject::RemoveChild(const std::string& name)
	{
		auto it = _children.begin();
		auto end = _children.end();
		while (it != end)
		{
			auto& child = *it;
			if (child->EqualByName(name))
			{
				if (_running)
				{
					child->OnExit();
				}
				child->SetParent(nullptr);
				child->_running = false;
				_children.erase(it);
				break;
			}

			++it;
		}
	}

	void GameObject::RemoveChildFromParent()
	{
		auto parent = GetParent();
		if (parent)
		{
			parent->RemoveChild(shared_from_this());
		}
	}

	void GameObject::RemoveAllChildren()
	{
		while (!_children.empty())
		{
			auto& child = _children.back();
			if (_running)
			{
				child->OnExit();
			}
			child->SetParent(nullptr);
			child->_running = false;
			_children.pop_back();
		}
	}

	std::shared_ptr<GameObject> GameObject::GetChild(const std::string& name) const
	{
		auto it = _children.begin();
		auto end = _children.end();
		while (it != end)
		{
			auto& child = *it;
			if (child->EqualByName(name))
			{
				return child;
			}

			++it;
		}
		return nullptr;
	}

	std::shared_ptr<GameObject> GameObject::GetChildByTag(const int& tag) const
	{
		auto it = _children.begin();
		auto end = _children.end();
		while (it != end)
		{
			auto& child = *it;
			if (child->EqualByTag(tag))
			{
				return child;
			}

			++it;
		}
		return nullptr;
	}

	const std::vector<std::shared_ptr<GameObject>>& GameObject::GetChildren() const
	{
		return _children;
	}

	void GameObject::SortChildren()
	{
		if (!_dirty)
		{
			return;
		}

		auto greater = [](std::shared_ptr<GameObject> left, std::shared_ptr<GameObject> right)
		{
			return left->GetDepth() < right->GetDepth();
		};

		std::sort(_children.begin(), _children.end(), greater);
		_dirty = false;
	}

	void GameObject::AddComponent(std::shared_ptr<Component> component)
	{
		if (component->GetOwner() != nullptr)
		{
			return;
		}

		_components.emplace_back(component);
		component->SetOwner(shared_from_this());
		if (_running)
		{
			component->OnEnter();
		}
	}

	void GameObject::RemoveComponent(const std::shared_ptr<Component>& component)
	{
		auto it = _components.begin();
		auto end = _components.end();
		while (it != end)
		{
			auto& comp = *it;
			if (comp == component)
			{
				if (_running)
				{
					comp->OnExit();
				}
				comp->SetOwner(nullptr);
				_components.erase(it);
			}
			++it;
		}
	}

	void GameObject::RemoveComponent(const std::string& name)
	{
		auto it = _components.begin();
		auto end = _components.end();
		while (it != end)
		{
			auto& comp = *it;
			if (comp->EqualByName(name))
			{
				if (_running)
				{
					comp->OnExit();
				}
				comp->SetOwner(nullptr);
				_components.erase(it);
			}
			++it;
		}
	}

	void GameObject::RemoveAllComponents()
	{
		while (!_components.empty())
		{
			auto& comp = _components.back();
			if (_running)
			{
				comp->OnExit();
			}
			comp->SetOwner(nullptr);
			_components.pop_back();
		}
	}

}