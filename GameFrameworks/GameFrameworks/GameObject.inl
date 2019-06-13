namespace meltshine
{
	template<typename T>
	inline void GameObject::RemoveComponent()
	{
		auto it = _components.begin();
		auto end = _components.end();
		while (it != end)
		{
			auto& comp = *it;
			if (typeid(*comp.get()) == typeid(T))
			{
				_components.erase(it);
			}
			++it;
		}
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent() const
	{
		for (auto& comp : _components)
		{
			if (typeid(T) == typeid(*comp.get()))
			{
				return std::static_pointer_cast<T>(comp);
			}
		}
		return nullptr;
	};

	template<typename T>
	inline std::shared_ptr<T> GameObject::GetComponent(const std::string& name) const
	{
		for (auto& comp : _components)
		{
			if (typeid(T) == typeid(*comp.get()) &&
				comp->EqualByName(name))
			{
				return std::static_pointer_cast<T>(comp);
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<std::shared_ptr<T>> GameObject::GetComponents() const
	{
		std::vector<std::shared_ptr<T>> components;
		for (auto& comp : _components)
		{
			if (typeid(*comp.get()) == typeid(T))
			{
				components.emplace_back(std::static_pointer_cast<T>(comp));
			}
		}
		return components;
	}

	inline bool GameObject::EqualByName(const std::string& name) const
	{
		return ((_hash_of_name == StrToHash(name)) && _name.compare(name));
	}
	inline bool GameObject::EqualByTag(const int& tag) const
	{
		return (_tag == tag);
	}

	inline size_t GameObject::StrToHash(const std::string& str) const
	{
		return std::hash<std::string>()(str);
	}	

}