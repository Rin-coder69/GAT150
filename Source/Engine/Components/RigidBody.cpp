#include "RigidBody.h"
#include "EnginePCH.h"

namespace gaia {
	FACTORY_REGISTER(RigidBody)
	void RigidBody::Update(float dt) {
		owner->transform.position += velocity * dt;
		velocity *= (1.0f / (1.0f + damping * dt)); // Apply damping
	}

	void RigidBody::Read(const json::value_t& value)
	{
		Object::Read(value);
	
		JSON_READ(value, damping);
	}
}