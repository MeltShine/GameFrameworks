#include "FontCache.h"

namespace meltshine
{
	FontCache::FontCache()
		: _d3d_device(nullptr)
	{
	}

	FontCache::~FontCache()
	{
		RemoveAllFont();
	}

	bool FontCache::Init(LPDIRECT3DDEVICE9 dev)
	{
		if (dev == nullptr)
		{
			return false;
		}
		_d3d_device = dev;

		if (!AddFont("Default", TEXT("Arial"), 20))
		{
			return false;
		}

		return true;
	}

	bool FontCache::AddFont(std::string key, LPD3DXFONT d3dx_font)
	{
		if (HasFont(key) || d3dx_font == nullptr)
		{
			return false;
		}

		_d3dx_fonts.emplace(key, d3dx_font);
		return true;
	}

	bool FontCache::AddFont(std::string key, const TCHAR* facename, INT height, UINT width, UINT weight, UINT mip_levels, BOOL italic)
	{
		if (HasFont(key))
		{
			return false;
		}

		LPD3DXFONT d3dx_font = nullptr;
		if (FAILED(D3DXCreateFont(
			_d3d_device,
			height,
			width,
			weight,
			mip_levels,
			italic,
			DEFAULT_CHARSET,
			OUT_DEFAULT_PRECIS,
			DEFAULT_QUALITY,
			DEFAULT_PITCH | FF_DONTCARE,
			facename,
			&d3dx_font)))
		{
			return false;
		}

		_d3dx_fonts.emplace(key, d3dx_font);
		return true;
	}

	void FontCache::RemoveFont(const std::string& key)
	{
		_d3dx_fonts.at(key)->Release();
		_d3dx_fonts.erase(key);
	}

	void FontCache::RemoveAllFont()
	{
		for (auto& pair : _d3dx_fonts)
		{
			auto d3dx_font = pair.second;
			if (d3dx_font != nullptr)
			{
				d3dx_font->Release();
				d3dx_font = nullptr;
			}
		}
		_d3dx_fonts.clear();
	}

	LPD3DXFONT FontCache::GetFont(const std::string& key)
	{
		return _d3dx_fonts.at(key);
	}

	bool FontCache::HasFont(const std::string& key) const
	{
		return _d3dx_fonts.find(key) != _d3dx_fonts.end();
	}

	bool FontCache::HasNotFont(const std::string& key) const
	{
		return _d3dx_fonts.find(key) == _d3dx_fonts.end();
	}

}