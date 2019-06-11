#ifndef __MELTSHINE_RENDERER_H__
#define __MELTSHINE_RENDERER_H__
#include <d3dx9.h>
#include <list>
#include <functional>
namespace meltshine
{
	class Renderer
	{
	private:
		Renderer();

	public:
		~Renderer();
		
		void Render();

	private:
		std::list<std::function<void()>> _draw_funcs;

		void DrawLine();
		void DrawSprite();

		friend class Core;
	};
}
#endif // !__MELTSHINE_RENDERER_H__
