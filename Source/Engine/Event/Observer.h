#pragma once
#include "Event.h"
namespace gaia {
	class IObserver {
	public:
		virtual ~IObserver();

		virtual void OnNotify(const Event& event) = 0;
	};
}