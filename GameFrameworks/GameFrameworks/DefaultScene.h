#pragma once
#include "Scene.h"
namespace meltshine
{
	class DefaultScene : public Scene
	{
	public:
		DefaultScene();
		virtual ~DefaultScene();

		virtual bool Init(std::shared_ptr<Core> core) override;
		virtual void Update(const float& dt) override;
		virtual void LateUpdate() override;
		virtual void Render() override;
	};
}
