#pragma once
#include "Component.h"

namespace gaia{
	class RigidBody : public Component {
	public:
		vec2 velocity{ 0,0 };
		float damping{ 0.0f }; // Damping factor to reduce velocity over time

	public:
		void Update(float dt) override;
			// Update the position based on velocity and apply damping

		};
	}
	
