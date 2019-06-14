#ifndef __MELTSHINE_OBJECTMANAGER_H__
#define __MELTSHINE_OBJECTMANAGER_H__
#include <unordered_map>
#include <memory>
namespace meltshine
{
	class Core;
	class GameObject;
	// Component
	class Component;
	class Transform;
	class Camera;
	class ObjectManager
	{
	private:
		ObjectManager();

	public:
		~ObjectManager();
		
		bool Init(std::shared_ptr<Core> core);

		// 게임 오브젝트
		std::shared_ptr<GameObject> CreateEmptyObject();

		// Prefeb
		void InsertOrigin(std::string key, std::shared_ptr<GameObject> obj);
		void RemoveOrigin(const std::string& key);
		void RemoveAllOrigin();
		bool HasOrigin(const std::string& key);
		std::shared_ptr<GameObject> GetOrigin(const std::string& key);

		// 컴포넌트
		template <typename T>
		std::shared_ptr<T> CreateComponent();

	private:
		std::weak_ptr<Core> _core;
		std::unordered_map<std::string, std::shared_ptr<GameObject>> _origin_objects;

		friend class Core;
	};
}
#include "ObjectManager.inl"
#endif // !__MELTSHINE_OBJECTMANAGER_H__