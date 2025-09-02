#pragma once
#include "Framework/Object.h"

namespace gaia {
	class Component : public Object {
		// Base class for all components in the game engine
	public:
		class Actor* owner{ nullptr }; // Pointer to the actor that owns this component
	public:
		Component() = default;

		virtual void Update(float dt) = 0;
		virtual void Start() {}
		virtual void Destroyed() {}
	};

}