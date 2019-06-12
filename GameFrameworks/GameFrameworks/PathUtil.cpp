#include "PathUtil.h"

namespace meltshine
{
	TCHAR PathUtil::_root_directory[MAX_PATH] = {};

	void PathUtil::Init()
	{
		TCHAR exe_path[MAX_PATH] = {};
		GetModuleFileName(NULL, exe_path, MAX_PATH);
		int pos = lstrlen(exe_path);
		while (pos > 0)
		{
			// 문자열 가장 뒤쪽부터 이스케이프 문자 '\\'의 위치를 찾는다.
			if (exe_path[pos] == '\\')
			{
				break;
			}
			--pos;
		}
		// 문자열을 복사할 때 이스케이프 문자 '\\'도 포함시키기 위해 '1'을 더해준다.
		memcpy(_root_directory, exe_path, pos + 1);
	}

	const TCHAR* PathUtil::GetDirectory()
	{
		return _root_directory;
	}

	const TCHAR* PathUtil::Combine(const TCHAR* filename)
	{
		TCHAR combined[MAX_PATH] = {};
		wsprintf(combined, TEXT("%s%s"), _root_directory, filename);
		return combined;
	}

}