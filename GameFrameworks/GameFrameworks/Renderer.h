#ifndef __MELTSHINE_RENDERER_H__
#define __MELTSHINE_RENDERER_H__
#include <d3dx9.h>
#include <list>
#include <string>
#include <functional>
namespace meltshine
{
	class Renderer
	{
	private:
		Renderer();

	public:
		~Renderer();
		
		bool Init(LPDIRECT3DDEVICE9 dev);
		void Clear(D3DCOLOR color, DWORD flag);
		void DrawLine(
			const D3DXVECTOR2* vertics,
			const DWORD& vertex_count,
			const D3DCOLOR& color,
			const FLOAT& width);
		void DrawLine(const D3DXVECTOR3* vertics,
			const DWORD& vertex_count,
			const D3DCOLOR& color,
			const FLOAT& width,
			const D3DXMATRIX* transform);
		void DrawSprite(
			const LPDIRECT3DTEXTURE9 texture,
			const D3DXMATRIX* transform, 
			const D3DCOLOR& color);
		void DrawString(
			const LPD3DXFONT font, 
			const std::string& str, 
			const LPRECT rect,
			const DWORD& format,
			const D3DCOLOR& color);
		void Render();

	private:
		std::list<std::function<void()>> _drawing_tasks;
		LPDIRECT3DDEVICE9  _d3d_device;
		LPDIRECT3DTEXTURE9 _d3d_test_texture;
		LPD3DXSPRITE	_d3dx_sprite;
		LPD3DXLINE		_d3dx_line;

		friend class Core;
	};
}
#endif // !__MELTSHINE_RENDERER_H__
