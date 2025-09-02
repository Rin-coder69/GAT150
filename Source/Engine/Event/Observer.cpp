#include "Observer.h"
#include "EventManager.h"

namespace gaia {
	gaia::IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}