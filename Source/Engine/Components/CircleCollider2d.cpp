#include "CircleCollider2d.h"
#include "ColliderComponents.h"
namespace gaia {
	void CircleCollider2d::Update(float dt) {
		// Initialization logic for CircleCollider2d if needed
	}

	bool CircleCollider2d::CheckCollision(ColliderComponent& other) const {
		float distance = (owner->transform.position - other.owner->transform.position).length();
		//check circle to circle collision
		auto circleCollider = dynamic_cast<CircleCollider2d*>(&other);
		if (circleCollider) {
			float radii = radius + circleCollider->radius;
			if (distance <= radii) return true;
		}
		return false;
	};
}