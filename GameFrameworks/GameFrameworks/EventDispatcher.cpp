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
		if (listener->is_registered_)
			return;

		listeners_.push_back(listener);
		listener->is_registered_ = true;
	}

	void EventDispatcher::RemoveEventListener(std::shared_ptr<EventListener> listener)
	{
		listeners_.remove(listener);
	}

	void EventDispatcher::RemoveAllEventListener()
	{
		while (!listeners_.empty())
		{
			listeners_.back()->is_registered_ = false;
			listeners_.pop_back();
		}
	}

	void EventDispatcher::DispatchEvent(Event* evt)
	{
		for (auto& listener : listeners_)
		{
			if (evt->IsStopped())
				break;
			listener->OnEvent(evt);
		}
	}
	
}