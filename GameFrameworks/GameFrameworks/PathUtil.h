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
		static const TCHAR* GetDirectory();
		static const TCHAR* Combine(const TCHAR* filename);

	private:
		static TCHAR _root_directory[MAX_PATH];
	};
}
#endif // !__MELTSHINE_PATHUTIL_H__
