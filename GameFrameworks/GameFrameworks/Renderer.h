#ifndef __MELTSHINE_RENDERER_H__
#define __MELTSHINE_RENDERER_H__
#include <d3dx9.h>
#include <list>
#include <vector>
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
		void Clear(const D3DCOLOR& color, const DWORD& flag);
		void BeginScene();
		void EndScene();

		void DrawLine(
			const std::vector<D3DXVECTOR2>& vertics,
			const D3DCOLOR& color,
			const FLOAT& width);
		void DrawLine(
			const std::vector<D3DXVECTOR3>& vertics,
			const D3DCOLOR& color,
			const FLOAT& width,
			const D3DXMATRIX& transform);
		void DrawString(
			const LPD3DXFONT font,
			const std::string& text,
			RECT rect,
			const D3DCOLOR& color);
		void DrawString(
			const LPD3DXFONT font,
			const std::wstring& text,
			RECT rect,
			const D3DCOLOR& color);
		void DrawSprite(
			const LPDIRECT3DTEXTURE9 tex,
			const D3DXMATRIX& transform, 
			const D3DCOLOR& color);
		void DrawSprite(
			const LPDIRECT3DTEXTURE9 tex,
			const RECT& src_rect,
			const D3DXVECTOR3& center,
			const D3DXVECTOR3& position,
			const D3DCOLOR& color);

		void Render();

		void GetRenderTarget(DWORD index, LPDIRECT3DSURFACE9* surface) const;
		void SetRenderTarget(DWORD index, LPDIRECT3DSURFACE9 surface);
		void SetTransform(D3DTRANSFORMSTATETYPE type, const D3DMATRIX& mat);

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
