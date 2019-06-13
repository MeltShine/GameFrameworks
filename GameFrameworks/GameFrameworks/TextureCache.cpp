#include "TextureCache.h"

namespace meltshine
{
	TextureCache::TextureCache()
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

	void TextureCache::AddTexture(std::string key, LPDIRECT3DTEXTURE9 d3d_texture)
	{
		if (HasTexture(key))
		{
			return;
		}

		_d3d_textures.emplace(key, d3d_texture);
	}

	void TextureCache::AddTexture(
		std::string key, 
		const TCHAR* filename, 
		const UINT& width,
		const UINT& height,
		const DWORD& usage,
		const D3DCOLOR& colorkey,
		const UINT& mip_levels)
	{
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
			return;
		}

		AddTexture(key, d3d_texture);
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
		_d3d_textures.erase(key);
	}

	void TextureCache::RemoveAllTexture()
	{
		for (auto& pair : _d3d_textures)
		{
			pair.second->Release();
		}
		_d3d_textures.clear();
	}

}