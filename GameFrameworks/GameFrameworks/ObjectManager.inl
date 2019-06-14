#ifndef __MELTSHINE_OBJECTMANAGER_INL__
#define __MELTSHINE_OBJECTMANAGER_INL__

namespace meltshine
{
	template<typename T>
	inline std::shared_ptr<T> ObjectManager::CreateComponent()
	{
		std::shared_ptr<T> comp(new T);
		if (comp && comp->Init(_core.lock()))
		{
			return comp;
		}
		return nullptr;
	}
}

#endif // !__MELTSHINE_OBJECTMANAGER_INL__

