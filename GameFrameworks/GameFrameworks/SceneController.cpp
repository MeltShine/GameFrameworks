#include "SceneController.h"
#include "Scene.h"

namespace meltshine
{
	SceneController::SceneController()
	{
	}

	SceneController::~SceneController()
	{
	}

	std::shared_ptr<Scene> SceneController::GetCurrentScene() const
	{
		return _scene_stack.top();
	}

	void SceneController::PushScene(std::shared_ptr<Scene> scene)
	{
		if (scene == nullptr || scene->_running == true)
		{
			return;
		}
		_scene_stack.push(scene);
		scene->_running = true;
		scene->OnEnter();
	}

	void SceneController::PopScene()
	{
		if (_scene_stack.size() <= 1)
		{
			return;
		}
		auto& scene = _scene_stack.top();
		scene->OnExit();
		scene->_running = false;
		_scene_stack.pop();
	}

	void SceneController::ChangeScene(std::shared_ptr<Scene> scene)
	{
		while (!_scene_stack.empty())
		{
			auto& scene = _scene_stack.top();
			scene->OnExit();
			scene->_running = false;
			_scene_stack.pop();
		}

		PushScene(scene);
	}

}