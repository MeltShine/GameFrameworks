#include "EventListener.h"


namespace meltshine
{
	Event::Event()
		: Event(ET_NONE)
	{
	}


	Event::Event(EventType type) 
		: _type(type)
		, _is_stopped(false)
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
		: _type(type)
		, _is_registered(false)
	{
	}


	EventListener::~EventListener()
	{
	}

}