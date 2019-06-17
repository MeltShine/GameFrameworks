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
		virtual ~Scene();

		virtual bool Init(std::shared_ptr<Core> core) override;
		virtual void LateUpdate() override;
		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;
		virtual void RenderImage() override;
		
		std::shared_ptr<Camera> GetVisitingCamera() const { return _visiting_camera; };
		std::shared_ptr<Camera> GetDefaultCamera() const { return _default_camera; };
		
		void SetVisitingCamera(std::shared_ptr<Camera> cam) { _visiting_camera = cam; };
		void SetDefaultCamera(std::shared_ptr<Camera> cam) { _default_camera = cam; };
		void SortCameras();

	protected:
		bool _dirty_cameras;
		std::vector<std::shared_ptr<Camera>> _cameras;
		std::shared_ptr<Camera> _visiting_camera;
		std::shared_ptr<Camera> _default_camera;

		friend class ObjectManager;
		friend class SceneController;
		friend class Camera;
	};
}
#endif // !__MELTSHINE_SCENE_H__
