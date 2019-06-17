#include "Renderer.h"

#include <memory>

#include "PathUtil.h"

namespace meltshine
{
	Renderer::Renderer()
		: _d3d_device(nullptr)
		, _d3dx_sprite(nullptr)
		, _d3dx_line(nullptr)
		, _d3d_test_texture(nullptr)
	{
	}

	Renderer::~Renderer()
	{
		if (_d3d_test_texture)
		{
			_d3d_test_texture->Release();
			_d3d_test_texture = nullptr;
		}
		if (_d3dx_sprite)
		{
			_d3dx_sprite->Release();
			_d3dx_sprite = nullptr;
		}
		if (_d3dx_line)
		{
			_d3dx_line->Release();
			_d3dx_line = nullptr;
		}
	}

	bool Renderer::Init(LPDIRECT3DDEVICE9 dev)
	{
		if (dev == nullptr)
		{
			return false;
		}

		_d3d_device = dev;
		if (FAILED(D3DXCreateSprite(_d3d_device, &_d3dx_sprite)))
		{
			return false;
		}
		if (FAILED(D3DXCreateLine(_d3d_device, &_d3dx_line)))
		{
			return false;
		}

		TCHAR filename[MAX_PATH] = {};
		wsprintf(filename, TEXT("%s%s"), PathUtil::GetDirectory(), "img/test.bmp");
		if (FAILED(D3DXCreateTextureFromFileEx(
			_d3d_device,
			filename,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT_NONPOW2,
			D3DX_DEFAULT,
			0,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			nullptr,
			nullptr,
			&_d3d_test_texture)))
		{
			return false;
		}

		return true;
	}

	void Renderer::Clear(const D3DCOLOR& color, const DWORD& flag)
	{
		auto clear = [=]() {
			_d3d_device->Clear(0, nullptr, flag, color, 1.0f, 0);
		};
		_drawing_tasks.emplace_back(std::move(clear));
	}

	void Renderer::BeginScene()
	{
		auto begin_scene = [&]()
		{
			_d3d_device->BeginScene();
		};

		_drawing_tasks.emplace_back(std::move(begin_scene));
	}

	void Renderer::EndScene()
	{
		auto end_scene = [&]()
		{
			_d3d_device->EndScene();
		};

		_drawing_tasks.emplace_back(std::move(end_scene));
	}

	void Renderer::DrawLine(
		const std::vector<D3DXVECTOR2>& vertics, 
		const D3DCOLOR& color,
		const FLOAT& width)
	{
		auto draw_line = [&, vertics, color, width]() {
			if (_d3dx_line->GetWidth() != width)
			{
				_d3dx_line->SetWidth(width);
			}
			_d3dx_line->Begin();
			_d3dx_line->Draw(vertics.data(), vertics.size(), color);
			_d3dx_line->End();
		};
		_drawing_tasks.emplace_back(std::move(draw_line));
	}

	void Renderer::DrawLine(
		const std::vector<D3DXVECTOR3>& vertics,
		const D3DCOLOR& color, 
		const FLOAT& width, 
		const D3DXMATRIX& transform)
	{
		auto draw_line = [&, vertics, color, width, transform]() {
			if (_d3dx_line->GetWidth() != width)
			{
				_d3dx_line->SetWidth(width);
			}
			_d3dx_line->Begin();
			_d3dx_line->DrawTransform(vertics.data(), vertics.size(), &transform, color);
			_d3dx_line->End();
		};
		_drawing_tasks.emplace_back(std::move(draw_line));
	}

	void Renderer::DrawString(
		const LPD3DXFONT font, 
		const std::string& text,
		RECT rect,
		const D3DCOLOR& color)
	{
		auto draw_string = [&, font, text, color, rect]() {
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			font->DrawTextA(_d3dx_sprite, text.c_str(), text.length(), (LPRECT)&rect, 0, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_string));
	}

	void Renderer::DrawString(
		const LPD3DXFONT font,
		const std::wstring& text,
		RECT rect,
		const D3DCOLOR& color)
	{
		auto draw_string = [&, font, text, color, rect]() {
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			font->DrawTextW(_d3dx_sprite, text.c_str(), text.length(), (LPRECT)& rect, 0, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_string));
	}

	void Renderer::DrawSprite(
		const LPDIRECT3DTEXTURE9 tex,
		const D3DXMATRIX& transform,
		const D3DCOLOR& color)
	{
		auto draw_sprite = [&, tex, transform, color]() {
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			_d3dx_sprite->SetTransform(&transform);
			_d3dx_sprite->Draw(tex, nullptr, nullptr, nullptr, color); 
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_sprite));
	}
	void Renderer::DrawSprite(
		const LPDIRECT3DTEXTURE9 tex,
		const RECT& src_rect,
		const D3DXVECTOR3& center,
		const D3DXVECTOR3& position, 
		const D3DCOLOR& color)
	{
		auto draw_sprite = [&, tex, src_rect, center, position, color]() {
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			_d3dx_sprite->Draw(tex, &src_rect, &center, &position, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_sprite));
	}
	void Renderer::Render()
	{
		for (auto task : _drawing_tasks)
		{
			task();
		}

		_d3d_device->Present(0, 0, 0, 0);
		_drawing_tasks.clear();
	}

	void Renderer::GetRenderTarget(DWORD index, LPDIRECT3DSURFACE9* surface) const
	{
		_d3d_device->GetRenderTarget(index, surface);
	}

	void Renderer::SetRenderTarget(DWORD index, LPDIRECT3DSURFACE9 surface)
	{
		_d3d_device->SetRenderTarget(index, surface);
	}

	void Renderer::SetTransform(D3DTRANSFORMSTATETYPE type, const D3DMATRIX& mat)
	{
		auto set_transform = [&, type, mat]() {
			_d3d_device->SetTransform(type, &mat);
		};

		_drawing_tasks.emplace_back(std::move(set_transform));
		
	}


}