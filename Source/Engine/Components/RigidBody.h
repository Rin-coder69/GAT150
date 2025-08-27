#pragma once
#include "Component.h"

namespace gaia {
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0,0 };
		float damping{ 0.0f };// Damping factor to reduce velocity over time
		void Read(const json::value_t& value) override;

	public:
		Class_PROTOTYPE(RigidBody)

			// Update function to apply physics
			void Update(float dt) override;
		// Update the position based on velocity and apply damping
		
	};
}
	
