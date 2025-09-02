#include "Observer.h"

namespace gaia {
	gaia::IObserver::~IObserver() {
		OBSERVER_REMOVE_SELF;
	}
}