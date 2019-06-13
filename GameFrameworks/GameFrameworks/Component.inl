namespace meltshine
{
	inline bool Component::EqualByName(const std::string& name) const
	{
		return ((_hash_of_name == StrToHash(name)) && _name.compare(name));
	}
	inline size_t Component::StrToHash(const std::string& str) const
	{
		return std::hash<std::string>()(str);
	}
}