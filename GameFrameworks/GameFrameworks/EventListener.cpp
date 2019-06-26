#include "EventListener.h"


namespace meltshine
{
	Event::Event()
		: Event(EventType::EVENT_NONE)
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
		: EventListener(EventType::EVENT_NONE)
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