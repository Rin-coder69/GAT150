#pragma once
#include "Components/Component.h"


class Enemy : public gaia::Component{
public:
	float speed = 200;
	float fireTime = 0;
	float fireTimer = 0;
public:
	Enemy() = default;
	/*(Enemy(const gaia::Transform& transform) :
		Actor{ transform }
	{}*/

	void Update(float deltaTime) override;
	// Inherited via Actor
	void OnCollision(class Actor* other) ;

};
