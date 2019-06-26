#include "EventDispatcher.h"
#include "EventListener.h"

namespace meltshine
{
	EventDispatcher::EventDispatcher()
	{
	}

	EventDispatcher::~EventDispatcher()
	{
	}

	EventDispatcher& EventDispatcher::GetInstance()
	{
		static EventDispatcher instance;
		return instance;
	}

	void EventDispatcher::AddEventListener(std::shared_ptr<EventListener> listener)
	{
		if (listener->_is_registered)
			return;

		_listeners.push_back(listener);
		listener->_is_registered = true;
	}

	void EventDispatcher::RemoveEventListener(std::shared_ptr<EventListener> listener)
	{
		_listeners.remove(listener);
	}

	void EventDispatcher::RemoveAllEventListener()
	{
		while (!_listeners.empty())
		{
			_listeners.back()->_is_registered = false;
			_listeners.pop_back();
		}
	}

	void EventDispatcher::DispatchEvent(Event* evt)
	{
		for (auto& listener : _listeners)
		{
			if (evt->IsStopped())
				break;
			listener->OnEvent(evt);
		}
	}
	
}