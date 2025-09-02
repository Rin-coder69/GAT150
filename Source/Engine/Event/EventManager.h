#pragma once
#include "Observer.h"
#include "Event.h"
#define OBSERVER_ADD(event_id)  gaia::EventManager::Instance().AddObserver(#event_id,this)
#define OBSERVER_REMOVE_SELF  gaia::EventManager::Instance().removeObserver(*this)
#define EVENT_NOTIFY_DATA(event_id,data) gaia::EventManager::Instance().notify({#event_id,data})
#define EVENT_NOTIFY(event_id) gaia::EventManager::Instance().notify({#event_id,true})

namespace gaia {
	class EventManager : public Singleton<EventManager> {
	public:
		void AddObserver(const Event::id_t& eventId, IObserver* observer);
		void removeObserver(IObserver& observer);
		void notify(const Event& event);
		void removeAll() { m_observers.clear(); }

	private:
		std::map<Event::id_t, std::list<IObserver*>> m_observers;
	};
}