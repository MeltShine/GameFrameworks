#ifndef __MELTSHINE_CORE_H__
#define __MELTSHINE_CORE_H__
#include <memory>
#include <Windows.h>
namespace meltshine
{
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
		HWND GetWinHandle() const;
		HINSTANCE GetWinInstance() const;

	private:
		HWND _window;
		HINSTANCE _instance;

	};
}
#endif // !__MELTSHINE_CORE_H__