#include "Component.h"
#include "GameObject.h"

namespace meltshine
{
	Component::Component()
	{
	}

	Component::~Component()
	{
	}

	void Component::SetName(std::string name)
	{
		if (EqualByName(name))
		{
			return;
		}

		_name = name;
		_hash_of_name = StrToHash(name);
	}
}