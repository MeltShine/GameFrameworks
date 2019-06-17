#include "TestCode.h"
#include "Core.h"
#include "Renderer.h"
#include "FontCache.h"
#include "TextureCache.h"
#include "GameObject.h"
#include "Transform.h"
namespace meltshine
{
	TestCode::TestCode()
	{
	}
	TestCode::~TestCode()
	{
	}
	bool TestCode::Init(std::shared_ptr<Core> core)
	{
		_renderer = core->GetRenderer();
		_font = core->GetFontCache()->GetFont("Default");
		core->GetTextureCache()->AddTexture("test", "test.bmp");
		_tex = core->GetTextureCache()->GetTexture("test");
		return true;
	}
	void TestCode::OnEnter()
	{
	}
	void TestCode::OnExit()
	{
	}
	void TestCode::Update(const float& dt)
	{
	}
	void TestCode::LateUpdate()
	{
	}
	void TestCode::PreRender()
	{
	}
	void TestCode::Render()
	{
		std::vector<D3DXVECTOR2> v;
		v = { {},{500,500} };
		_renderer->DrawLine(v, 0xFFFF00FF, 2.0f);

		RECT r = {0,0,500,500};
		_renderer->DrawString(_font, "Hello World", r, D3DCOLOR_ARGB(255, 255, 255, 0));
		_renderer->DrawSprite(_tex, GetOwner()->GetTransform()->GetTransformMatrix(), 0xFFFFFFFF);
	}
	void TestCode::PostRender()
	{
	}
	void TestCode::RenderImage()
	{
	}
}