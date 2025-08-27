#pragma once
#include "ColliderComponents.h"
namespace gaia {
	class CircleCollider2d : public ColliderComponent {
	public:
		void Update(float dt);
		void Read(const json::value_t& value) override;

		float radius{ 0.0f }; // Radius of the circle collider
		bool CheckCollision(ColliderComponent& other) const override;
	};
}