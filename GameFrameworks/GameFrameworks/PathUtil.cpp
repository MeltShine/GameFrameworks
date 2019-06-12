#include "PathUtil.h"

namespace meltshine
{
	TCHAR PathUtil::_root_directory[MAX_PATH] = {};
	TCHAR PathUtil::_binary_directory[MAX_PATH] = {};

	void PathUtil::Init()
	{
		TCHAR exe_path[MAX_PATH] = {};
		GetModuleFileName(NULL, exe_path, MAX_PATH);
		int pos = lstrlen(exe_path);
		// ���� ���� ���
		{
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
			memcpy(_binary_directory, exe_path, pos + 1);
		}
		// ��Ʈ ���
		{
			--pos;
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
	}

	const TCHAR* PathUtil::GetBinaryDirectory()
	{
		return _binary_directory;
	}

	const TCHAR* PathUtil::GetDirectory()
	{
		return _root_directory;
	}

}