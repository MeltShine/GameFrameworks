#ifndef __MELTSHINE_FONTCACHE_H__
#define __MELTSHINE_FONTCACHE_H__
#include <unordered_map>
#include <d3dx9.h>
namespace meltshine
{
	class FontCache
	{
	private:
		FontCache();
	public:
		~FontCache();

		bool Init(LPDIRECT3DDEVICE9 dev);
		bool AddFont(std::string key, LPD3DXFONT d3dx_font);
		bool AddFont(
			std::string key,
			const TCHAR* facename, 
			INT height, UINT width = 0,
			UINT weight = FW_DONTCARE,
			UINT mip_levels = 1,
			BOOL italic = FALSE);
		void RemoveFont(const std::string& key);
		void RemoveAllFont();
		LPD3DXFONT GetFont(const std::string& key);
		bool HasFont(const std::string& key) const;
		bool HasNotFont(const std::string& key) const;

	private:
		LPDIRECT3DDEVICE9 _d3d_device;
		std::unordered_map<std::string, LPD3DXFONT> _d3dx_fonts;

		friend class Core;
	};
}
#endif // !__MELTSHINE_FONTCACHE_H__
