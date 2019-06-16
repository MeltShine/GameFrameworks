#ifndef __MELTSHINE_SCENE_H__
#define __MELTSHINE_SCENE_H__
#include <memory>
#include <vector>
#include "GameObject.h"
namespace meltshine
{
	class ObjectManager;
	class Camera;
	class Scene : public GameObject
	{
	protected:
		Scene();
	public:
		~Scene();

		virtual bool Init(std::shared_ptr<Core> core) override;
		/*virtual void Update(const float& dt) override;
		virtual void LateUpdate() override;
		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;
		virtual void RenderImage() override;*/

	protected:
		std::vector<std::shared_ptr<Camera>> _cameras;

		friend class ObjectManager;
		friend class SceneController;
	};
}
#endif // !__MELTSHINE_SCENE_H__
