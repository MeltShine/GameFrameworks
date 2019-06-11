#include "ConfigUtil.h"

#pragma warning(disable:4996)

namespace meltshine
{
	TCHAR ConfigUtil::_config_file_path[MAX_PATH];

	void ConfigUtil::Init(const TCHAR* root_path)
	{
		wsprintf(_config_file_path, TEXT("%s%s"), root_path, TEXT("GameOption.ini"));
	}

	void ConfigUtil::Write(const TCHAR* section, const TCHAR* key, const TCHAR* str)
	{
		WritePrivateProfileString(section, key, str, _config_file_path);
	}

	void ConfigUtil::Write(const TCHAR* section, const TCHAR* key, const int& num)
	{
		// int가 표현할 수 있는 최대값은 2,147,483,647이다.
		// 여기에 추가로 +/- 부호만큼 문자배열을 생성한다.
		TCHAR bf[11];
		
#ifdef _UNICODE
		_itow_s(num, bf, 11, 10);
#else
		_itoa_s(num, bf, 11, 10);
#endif // _UNICODE

		Write(section, key, bf);	
	}

#ifdef _UNICODE
	std::wstring ConfigUtil::ReadString(const TCHAR* section, const TCHAR* key, const size_t& size)
	{
		std::wstring str(size, 0);
		GetPrivateProfileString(section, key, 0, &str[0], size, _config_file_path);

		return str;
	}
#else
	std::string ConfigUtil::ReadString(const TCHAR* section, const TCHAR* key, const size_t& size)
	{
		std::string str(size, 0);
		GetPrivateProfileString(section, key, 0, &str[0], size, _config_file_path);

		return str;
	}
#endif // _UNICODE

	int ConfigUtil::ReadInt(const TCHAR* section, const TCHAR* key)
	{
		return GetPrivateProfileInt(section, key, 0, _config_file_path);
	}

}