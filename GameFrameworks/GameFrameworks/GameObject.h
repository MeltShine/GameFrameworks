#ifndef __MELTSHINE_GAMEOBJECT_H__
#define __MELTSHINE_GAMEOBJECT_H__
#include <memory>
#include <string>
#include <vector>
namespace meltshine
{
	class Core;
	class Direct3D;
	class Renderer;
	class ObjectManager;
	class Scene;
	class SceneController;
	class Component;
	class Transform;
	class GameObject : public std::enable_shared_from_this<GameObject>
	{
	protected:
		GameObject();
	public:
		virtual ~GameObject();

		virtual bool Init(std::shared_ptr<Core> core);
		virtual void OnEnter();
		virtual void OnExit();
		virtual void Update(const float& dt);
		virtual void LateUpdate();
		virtual void PreRender();
		virtual void Render();
		virtual void PostRender();
		virtual void RenderImage();

		// Setters
		void SetName(std::string name);
		void SetTag(int tag) { _tag = tag; };
		void SetDepth(int depth) { _depth = depth; };
		void SetVisible(bool is_visible) { _visible = is_visible; };
		void SetParent(std::shared_ptr<GameObject> obj) { _parent = obj; };
		void SetCore(std::shared_ptr<Core> core) { _core = core; };
		void SetDirect3D(std::shared_ptr<Direct3D> d3d) { _d3d = d3d; };
		void SetRenderer(std::shared_ptr<Renderer> renderer) { _renderer = renderer; };
		void SetObjectManager(std::shared_ptr<ObjectManager> obj_mgr) { _obj_mgr = obj_mgr; };
		void SetSceneController(std::shared_ptr<SceneController> sc_ctrl) { _sc_ctrl = sc_ctrl; };

		// Getters
		std::string GetName() const { return _name; };
		int GetTag() const { return _tag; };
		int GetDepth() const { return _depth; };
		bool IsRunning() const { return _running; };
		bool IsVisible() const { return _visible; };
		std::shared_ptr<GameObject> GetParent() const { return _parent.lock(); };
		std::shared_ptr<Core>		GetCore() const { return _core.lock(); };
		std::shared_ptr<Direct3D>	GetDirect3D() const { return _d3d.lock(); };
		std::shared_ptr<Renderer>	GetRenderer() const { return _renderer.lock(); };
		std::shared_ptr<ObjectManager> GetObjectManager() const { return _obj_mgr.lock(); };
		std::shared_ptr<Transform>  GetTransform() const { return _transform; };
		std::shared_ptr<SceneController> GetSceneController() const { return _sc_ctrl.lock(); };

		// Children
		virtual void AddChild(std::shared_ptr<GameObject> obj);
		bool HasChild(std::shared_ptr<GameObject> obj);
		void RemoveChild(std::shared_ptr<GameObject> obj);
		void RemoveChild(const std::string& name);
		void RemoveChildFromParent();
		void RemoveAllChildren();
		std::shared_ptr<GameObject> GetChild(const std::string& name) const;
		std::shared_ptr<GameObject> GetChildByTag(const int& tag) const;
		const std::vector<std::shared_ptr<GameObject>>& GetChildren() const;
		void SortChildren();

		// Components
		void AddComponent(std::shared_ptr<Component> component);
		void RemoveComponent(const std::shared_ptr<Component>& component);
		void RemoveComponent(const std::string& name);
		template <typename T>
		void RemoveComponent();
		void RemoveAllComponents();
		template <typename T>
		std::shared_ptr<T> GetComponent() const;
		template <typename T>
		std::shared_ptr<T> GetComponent(const std::string& name) const;
		const std::vector<std::shared_ptr<Component>>& GetComponents() const { return _components; }
		template <typename T>
		std::vector<std::shared_ptr<T>> GetComponents() const;

		// inlines
		inline bool EqualByName(const std::string& name) const;
		inline bool EqualByTag(const int& tag) const;
		inline size_t StrToHash(const std::string& str) const;

	protected:
		std::string _name;
		size_t		_hash_of_name;
		int			_tag;
		int			_depth;
		bool		_running;
		bool		_visible;
		bool		_dirty;
		std::weak_ptr<GameObject>	_parent;
		std::vector<std::shared_ptr<GameObject>> _children;
		std::vector<std::shared_ptr<Component>>  _components;
		std::shared_ptr<Transform> _transform;

		std::weak_ptr<Core> _core;
		std::weak_ptr<Direct3D> _d3d;
		std::weak_ptr<Renderer> _renderer;
		std::weak_ptr<ObjectManager> _obj_mgr;
		std::weak_ptr<SceneController> _sc_ctrl;

		friend class Scene;
		friend class ObjectManager;
	};
}
#include "GameObject.inl"
#endif // !__MELTSHINE_GAMEOBJECT_H__
