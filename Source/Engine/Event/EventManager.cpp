#include "Event/EventManager.h"

namespace gaia{
	void EventManager::AddObserver(const Event::id_t& eventId, IObserver* observer) {
		m_observers[tolower(eventId)].push_back(observer);
	}
	void EventManager::removeObserver(IObserver* observer) {
		for (auto& [eventId, observers] : m_observers) {
			observers.remove(observer);
		}
	}
	void EventManager::notify(const Event& event) {
		auto it = m_observers.find(event.id);
		if (it != m_observers.end()) {
			for (auto* observer : it->second) {
				if (observer) {
					observer->OnNotify(event);
				}
			}
		}
	}
}