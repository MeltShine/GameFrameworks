#ifndef __MELTSHINE_CONFIGUTIL_H__
#define __MELTSHINE_CONFIGUTIL_H__

#include <Windows.h>
#include <string>

namespace meltshine
{
	class ConfigUtil
	{
	public:
		static void Init(const TCHAR* root_path);
		static void Write(const TCHAR* section, const TCHAR* key, const TCHAR* str);
		static void Write(const TCHAR* section, const TCHAR* key, const int& num);
#ifdef _UNICODE
		static std::wstring ReadString(const TCHAR* section, const TCHAR* key, const size_t& size);
#else
		static std::string ReadString(const TCHAR* section, const TCHAR* key, const size_t& size);
#endif // _UNICODE

		static int ReadInt(const TCHAR* section, const TCHAR* key);

	private:
		static TCHAR _config_file_path[MAX_PATH];
	};
}
#endif // !__MELTSHINE_CONFIGUTIL_H__