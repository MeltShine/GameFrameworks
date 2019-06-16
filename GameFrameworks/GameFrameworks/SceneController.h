#ifndef __MELTSHINE_SCENECONTROLLER_H__
#define __MELTSHINE_SCENECONTROLLER_H__
#include <memory>
#include <stack>
namespace meltshine
{
	class Scene;
	class SceneController
	{
	private:
		SceneController();
	public:
		~SceneController();

		// GetCurrentScene
		// 장면 스택에서 가장 최상위에 있는 장면을 반환합니다.
		std::shared_ptr<Scene> GetCurrentScene() const;
		
		// PushScene
		// 현재 장면을 유지한채 새로운 장면을 추가합니다.
		// 단, 이전 장면들은 업데이트 및 렌더링을 하지않습니다.
		void PushScene(std::shared_ptr<Scene> scene);

		// PopScene
		// 장면 스택에서 최상위에 있는 장면을 꺼냅니다.
		// 단, 마지막 하나는 꺼내지 않습니다.
		void PopScene();

		// ChangeScene
		// 장면 스택 내 모든 장면을 꺼냅니다.
		// 그 후 입력받은 새로운 장면을 넣습니다.
		void ChangeScene(std::shared_ptr<Scene> scene);

	private:
		std::stack<std::shared_ptr<Scene>> _scene_stack;

		friend class Core;
	};
}
#endif // !__MELTSHINE_SCENECONTROLLER_H__