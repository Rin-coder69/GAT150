#pragma once
#include "Framework/Actor.h"

class Rocket : public gaia::Actor {

public:
	float speed = 200.0f;

public:
	Rocket() = default;
	Class_PROTOTYPE(Rocket)
	Rocket(const gaia::Transform& transform/*, gaia::res_t<gaia::Texture> texture*/ ) :
		gaia::Actor{transform}
	{}
	void Update(float deltaTime) override;
	// Inherited via Actor
	void OnCollision(Actor* other) override;
};