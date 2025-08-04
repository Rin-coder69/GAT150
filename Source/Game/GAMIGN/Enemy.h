#pragma once
#pragma once
#include "Framework/Actor.h"

class Enemy : public gaia::Actor {
public:
	float speed = 200;
	float fireTime = 0;
	float fireTimer = 0;
public:
	Enemy() = default;
	Enemy(const gaia::Transform& transform, std::shared_ptr<class gaia::Model> model) :
		gaia::Actor{ transform, model }
	{}

	void Update(float deltaTime) override;
	// Inherited via Actor
	void OnCollision(Actor* other) override;

};
