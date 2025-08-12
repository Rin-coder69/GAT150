#include "RigidBody.h"

namespace gaia {
	void RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt)); // Apply damping
	}
}