#ifndef __MELTSHINE_CORE_H__
#define __MELTSHINE_CORE_H__
#include <memory>
#include <Windows.h>
namespace meltshine
{
	class Direct3D;
	class Renderer;
	class FontCache;
	class Core : public std::enable_shared_from_this<Core>
	{
	private:
		Core();

	public:
		Core(const Core&) = delete;
		void operator=(const Core&) = delete;
		~Core();

		static std::shared_ptr<Core> Create();

		bool Init(HWND window, HINSTANCE instance);
		void Run();
		void GetWinSize(int& w, int& h) const;
		int GetWinWidth() const;
		int GetWinHeight() const;
		HWND GetWinHandle() const { return _window; }
		HINSTANCE GetWinInstance() const { return _instance; }

		std::shared_ptr<Direct3D> GetDirect3D() const { return _d3d; }
		std::shared_ptr<Renderer> GetRenderer() const { return _renderer; }
		std::shared_ptr<FontCache> GetFontCache() const { return _font_cache; }

	private:
		HWND _window;
		HINSTANCE _instance;
		std::shared_ptr<Direct3D> _d3d;
		std::shared_ptr<Renderer> _renderer;
		std::shared_ptr<FontCache> _font_cache;

	};
}
#endif // !__MELTSHINE_CORE_H__