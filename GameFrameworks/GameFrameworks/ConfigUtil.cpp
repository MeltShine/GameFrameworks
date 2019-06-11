#include "ConfigUtil.h"
namespace meltshine
{
	TCHAR ConfigUtil::_config_file_path[MAX_PATH];

	void ConfigUtil::Init(const TCHAR* root_path)
	{
		wsprintf(_config_file_path, TEXT("%s%s"), root_path, TEXT("GameOption.ini"));
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