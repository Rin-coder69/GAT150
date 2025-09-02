#pragma once
#include "Event.h"
#include "EventManager.h"
namespace gaia {
	class IObserver {
	public:
		virtual ~IObserver();

		virtual void OnNotify(const Event& event) = 0;
	};
}