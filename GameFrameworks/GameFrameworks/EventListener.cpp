#include "EventListener.h"


namespace meltshine
{
	Event::Event()
		: Event(ET_NONE)
	{
	}


	Event::Event(EventType type) 
		: type_(type)
		, is_stopped_(false)
	{
	}

	Event::~Event()
	{
	}

	EventListener::EventListener()
		: EventListener(ET_NONE)
	{
	}

	EventListener::EventListener(EventType type)
		: type_(type)
		, is_registered_(false)
	{
	}


	EventListener::~EventListener()
	{
	}

}