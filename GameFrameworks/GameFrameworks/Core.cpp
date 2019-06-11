#include "Core.h"

#ifdef _DEBUG
#define CRTDBG_MAP_ALLOC
#include <crtdbg.h>
// #include <new.h>������ operator new�� malloc�� 
// Derived�ؼ� ���� �� ���, ��� �� �� ����.
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
				TEXT("Core�� �ʱ�ȭ�ϴµ� �����߽��ϴ�. :\n ���� 'window' �Ǵ� 'instance'�� ��ȿ���� �ʽ��ϴ�."),
				TEXT("MeltShine GameFrameworks Error!"), MB_OK);
			return false;
		}

		// ��� ����
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