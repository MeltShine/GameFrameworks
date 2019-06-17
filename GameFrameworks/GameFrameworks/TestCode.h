#pragma once
#include "Component.h"
#include "FontCache.h"

namespace meltshine
{
	class Renderer;
	class TestCode : public Component
	{
	public:
		TestCode();
		virtual ~TestCode();

		// Component을(를) 통해 상속됨
		virtual bool Init(std::shared_ptr<Core> core) override;
		virtual void OnEnter() override;
		virtual void OnExit() override;
		virtual void Update(const float& dt) override;
		virtual void LateUpdate() override;
		virtual void PreRender() override;
		virtual void Render() override;
		virtual void PostRender() override;
		virtual void RenderImage() override;
	private:
		std::shared_ptr<Renderer> _renderer;
		ID3DXFont* _font;
		LPDIRECT3DTEXTURE9 _tex;
	};
}
