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
			// ���ڿ� ���� ���ʺ��� �̽������� ���� '\\'�� ��ġ�� ã�´�.
			if (exe_path[pos] == '\\')
			{
				break;
			}
			--pos;
		}
		// ���ڿ��� ������ �� �̽������� ���� '\\'�� ���Խ�Ű�� ���� '1'�� �����ش�.
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