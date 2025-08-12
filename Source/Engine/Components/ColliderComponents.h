#pragma once
#include "Component.h"

namespace gaia {
	class ColliderComponent : public Component {
	public:
		virtual bool CheckCollision(ColliderComponent& other) const = 0;
	};
}