#ifndef __MELTSHINE_COMPONENT_H__
#define __MELTSHINE_COMPONENT_H__
#include <memory>
#include <string>
namespace meltshine
{
	class GameObject;
	class Component
	{
	public:
		Component();
		~Component();

		virtual void OnEnter() = 0;
		virtual void OnExit()  = 0;
		virtual void Update(const float& dt) = 0;
		virtual void LateUpdate() = 0;
		virtual void PreRender()  = 0;
		virtual void Render() = 0;
		virtual void PostRender()  = 0;
		virtual void RenderImage() = 0;

		// setters
		void SetOwner(std::shared_ptr<GameObject> obj) { _owner = obj; };
		void SetName(std::string name);

		// getters
		std::shared_ptr<GameObject> GetOwner() const { return _owner.lock(); };
		std::string GetName() const { return _name; };

		// inlines
		inline bool EqualByName(const std::string& name) const;
		inline size_t StrToHash(const std::string& str) const;

	protected:
		std::weak_ptr<GameObject> _owner;
		std::string _name;
		size_t		_hash_of_name;

	};
}
#include "Component.inl"
#endif // !__MELTSHINE_COMPONENT_H__