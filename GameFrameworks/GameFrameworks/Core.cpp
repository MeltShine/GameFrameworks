#include "Core.h"

#ifdef _DEBUG
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// #include <new.h>등으로 operator new나 malloc을 
// Derived해서 정의 한 경우, 사용 할 수 없다.
#define new new( _NORMAL_BLOCK, __FILE__, __LINE__ )
#endif

#include "PathUtil.h"

namespace meltshine
{
	Core::Core()
		: _window(nullptr)
		, _instance(nullptr)
	{
	}

	Core::~Core()
	{
	}

	std::shared_ptr<Core> Core::Create()
	{
		return std::shared_ptr<Core>(new Core);
	}

	bool Core::Init(HWND window, HINSTANCE instance)
	{
		_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

		if (!window || !instance)
		{
			MessageBox(
				0, 
				TEXT("Core를 초기화하는데 실패했습니다. :\n 인자 'window' 또는 'instance'가 유효하지 않습니다."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		// 멤버 설정
		_window = window;
		_instance = instance;

		PathUtil::Init();
		return true;
	}

	void Core::Run()
	{
	}

	void Core::GetWinSize(int& w, int& h) const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		w = rect.right - rect.left;
		h = rect.bottom - rect.top;
	}

	int Core::GetWinWidth() const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		return rect.right - rect.left;
	}

	int Core::GetWinHeight() const
	{
		RECT rect = {};
		GetClientRect(_window, &rect);
		return rect.bottom - rect.top;
	}

	HWND Core::GetWinHandle() const
	{
		return _window;
	}

	HINSTANCE Core::GetWinInstance() const
	{
		return _instance;
	}

}