#include "Renderer.h"

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

	void Renderer::Clear(D3DCOLOR color, DWORD flag)
	{
		auto clear = [&]() {
			_d3d_device->Clear(0, nullptr, flag, color, 1.0f, 0);
		};

		_drawing_tasks.emplace_back(std::move(clear));
	}

	void Renderer::DrawLine(const D3DXVECTOR2* vertics, const DWORD& vertex_count, const D3DCOLOR& color, const FLOAT& width)
	{
		auto draw_line = [&]() {
			if (_d3dx_line->GetWidth() != width)
			{
				_d3dx_line->SetWidth(width);
			}
			_d3dx_line->Begin();
			_d3dx_line->Draw(vertics, vertex_count, color);
			_d3dx_line->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_line));
	}

	void Renderer::DrawLine(
		const D3DXVECTOR3* vertics,
		const DWORD& vertex_count,
		const D3DCOLOR& color,
		const FLOAT& width,
		const D3DXMATRIX* transform)
	{
		auto draw_line = [&]() {
			if (_d3dx_line->GetWidth() != width)
			{
				_d3dx_line->SetWidth(width);
			}
			_d3dx_line->Begin();
			if (transform)
			{
				_d3dx_line->DrawTransform(vertics, vertex_count, transform, color);
			}
			_d3dx_line->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_line));
	}

	void Renderer::DrawSprite(const LPDIRECT3DTEXTURE9 texture, const D3DXMATRIX* transform, const D3DCOLOR& color)
	{
		auto draw_sprite = [&]() {
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			if (transform != nullptr)
			{
				_d3dx_sprite->SetTransform(transform);
			}
			_d3dx_sprite->Draw(texture ? texture : _d3d_test_texture, nullptr, nullptr, nullptr, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_sprite));
	}

	void Renderer::DrawString(
		const LPD3DXFONT font,
		const std::string& str, 
		const LPRECT rect,
		const DWORD& format, 
		const D3DCOLOR& color)
	{
		auto draw_string = [&]()
		{
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			font->DrawTextA(_d3dx_sprite, str.c_str(), str.length(), rect, format, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_string));
	}

	void Renderer::DrawString(
		const LPD3DXFONT font,
		const std::wstring& wstr,
		const LPRECT rect,
		const DWORD& format,
		const D3DCOLOR& color)
	{
		auto draw_string = [&]()
		{
			_d3dx_sprite->Begin(D3DXSPRITE_ALPHABLEND);
			font->DrawTextW(_d3dx_sprite, wstr.c_str(), wstr.length(), rect, format, color);
			_d3dx_sprite->End();
		};

		_drawing_tasks.emplace_back(std::move(draw_string));
	}

	void Renderer::Render()
	{
		_d3d_device->BeginScene();
		for (auto task : _drawing_tasks)
		{
			task();
		}
		_d3d_device->EndScene();
		_d3d_device->Present(nullptr, nullptr, nullptr, nullptr);
		_drawing_tasks.clear();
	}


}