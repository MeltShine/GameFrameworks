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
		// ��� ���ÿ��� ���� �ֻ����� �ִ� ����� ��ȯ�մϴ�.
		std::shared_ptr<Scene> GetCurrentScene() const;
		
		// PushScene
		// ���� ����� ������ä ���ο� ����� �߰��մϴ�.
		// ��, ���� ������ ������Ʈ �� �������� �����ʽ��ϴ�.
		void PushScene(std::shared_ptr<Scene> scene);

		// PopScene
		// ��� ���ÿ��� �ֻ����� �ִ� ����� �����ϴ�.
		// ��, ������ �ϳ��� ������ �ʽ��ϴ�.
		void PopScene();

		// ChangeScene
		// ��� ���� �� ��� ����� �����ϴ�.
		// �� �� �Է¹��� ���ο� ����� �ֽ��ϴ�.
		void ChangeScene(std::shared_ptr<Scene> scene);

	private:
		std::stack<std::shared_ptr<Scene>> _scene_stack;

		friend class Core;
	};
}
#endif // !__MELTSHINE_SCENECONTROLLER_H__