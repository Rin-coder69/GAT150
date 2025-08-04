#pragma once
#include "Framework/Actor.h"

class Rocket : public gaia::Actor {
public:
	float speed = 200.0f;

public:
	Rocket() = default;
	Rocket(const gaia::Transform& transform, std::shared_ptr<class gaia::Model> model) :
		gaia::Actor{ transform, model }
	{}
	void Update(float deltaTime) override;
private:
	// Inherited via Actor
	void OnCollision(Actor* other) override;
};