#include "TextureCache.h"

namespace meltshine
{
	TextureCache::TextureCache()
		: _d3d_device(nullptr)
	{
	}

	TextureCache::~TextureCache()
	{
		RemoveAllTexture();
	}

	bool TextureCache::Init(LPDIRECT3DDEVICE9 dev)
	{
		if (dev == nullptr)
		{
			return false;
		}

		_d3d_device = dev;
		return true;
	}

	bool TextureCache::AddTexture(std::string key, LPDIRECT3DTEXTURE9 d3d_texture)
	{
		if (HasTexture(key) || d3d_texture == nullptr)
		{
			return false;
		}

		_d3d_textures.emplace(key, d3d_texture);
		return true;
	}

	bool TextureCache::AddTexture(
		std::string key, 
		const TCHAR* filename, 
		const UINT& width,
		const UINT& height,
		const DWORD& usage,
		const D3DCOLOR& colorkey,
		const UINT& mip_levels)
	{
		if (HasTexture(key))
		{
			return false;
		}

		LPDIRECT3DTEXTURE9 d3d_texture = nullptr;
		if (FAILED(D3DXCreateTextureFromFileEx(
			_d3d_device,
			filename,
			width,
			height,
			mip_levels,
			usage,
			D3DFMT_UNKNOWN,
			D3DPOOL_MANAGED,
			D3DX_DEFAULT,
			D3DX_DEFAULT,
			colorkey,
			nullptr,
			nullptr,
			&d3d_texture)))
		{
			return false;
		}

		_d3d_textures.emplace(key, d3d_texture);
		return true;
	}

	bool TextureCache::HasTexture(const std::string& key) const
	{
		return _d3d_textures.find(key) != _d3d_textures.end();
	}

	bool TextureCache::HasNotTexture(const std::string& key) const
	{
		return _d3d_textures.find(key) == _d3d_textures.end();
	}

	LPDIRECT3DTEXTURE9 TextureCache::GetTexture(const std::string& key) const
	{
		return _d3d_textures.at(key);
	}

	void TextureCache::RemoveTexture(const std::string& key)
	{
		auto& d3d_texture = _d3d_textures.at(key);
		if (d3d_texture != nullptr)
		{
			d3d_texture->Release();
			d3d_texture = nullptr;
		}

		_d3d_textures.erase(key);
	}

	void TextureCache::RemoveAllTexture()
	{
		for (auto& pair : _d3d_textures)
		{
			auto& d3d_texture = pair.second;
			if (d3d_texture != nullptr)
			{
				d3d_texture->Release();
				d3d_texture = nullptr;
			}
		}
		_d3d_textures.clear();
	}

}