#ifndef __MELTSHINE_TEXTURECACHE_H__
#define __MELTSHINE_TEXTURECACHE_H__
#include <unordered_map>
#include <d3dx9.h>
namespace meltshine
{
	class TextureCache
	{
	private:
		TextureCache();
	public:
		~TextureCache();

		bool Init(LPDIRECT3DDEVICE9 dev);
		bool AddTexture(std::string key, LPDIRECT3DTEXTURE9 d3d_texture);
		bool AddTexture(
			std::string key,
			const TCHAR* filename, 
			const UINT& width = D3DX_DEFAULT_NONPOW2,
			const UINT& height = D3DX_DEFAULT_NONPOW2,
			const DWORD& usage = 0,
			const D3DCOLOR& colorkey = 0,
			const UINT& mip_levels = 0);
		bool HasTexture(const std::string& key) const;
		bool HasNotTexture(const std::string& key) const;
		LPDIRECT3DTEXTURE9 GetTexture(const std::string& key) const;
		void RemoveTexture(const std::string& key);
		void RemoveAllTexture();

	private:
		LPDIRECT3DDEVICE9 _d3d_device;
		std::unordered_map<std::string, LPDIRECT3DTEXTURE9> _d3d_textures;

		friend class Core;
	};
}
#endif // !__MELTSHINE_TEXTURECACHE_H__
