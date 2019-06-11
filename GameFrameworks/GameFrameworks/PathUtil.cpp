#include "PathUtil.h"

namespace meltshine
{
	TCHAR PathUtil::_root_path[MAX_PATH] = {};

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
		memcpy(_root_path, exe_path, pos + 1);
	}

	const TCHAR* PathUtil::GetRoot()
	{
		return _root_path;
	}

}