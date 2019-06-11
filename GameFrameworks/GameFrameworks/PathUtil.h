#ifndef __MELTSHINE_PATHUTIL_H__
#define __MELTSHINE_PATHUTIL_H__
#include <Windows.h>
#include <string>
namespace meltshine
{
	class PathUtil
	{
	public:
		static void Init();
		static const TCHAR* GetRoot();

	private:
		static TCHAR _root_path[MAX_PATH];
	};
}
#endif // !__MELTSHINE_PATHUTIL_H__
