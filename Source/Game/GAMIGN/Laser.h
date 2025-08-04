#pragma once
#include "Framework/Actor.h"

class Laser : public gaia:: Actor {
public:
	float speed = 200.0f;

public:
	Laser() = default;
	Laser(const gaia::Transform& transform, std::shared_ptr<class gaia::Model> model) :
		gaia::Actor{ transform, model }
	{}
	void Update(float deltaTime) override;
	// Inherited via Actor
	void OnCollision(Actor* other) override;
};
