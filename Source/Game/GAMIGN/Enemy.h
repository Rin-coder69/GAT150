#pragma once
#include "Components/Component.h"
#include "Core/Factory.h"


class Enemy : public gaia::Component{
public:
	float speed = 200;
	float fireTime = 0;
	float fireTimer = 0;

public:
	Enemy() = default;
	
	Class_PROTOTYPE(Enemy);


	void Update(float deltaTime) override;
	// Inherited via Actor
	void OnCollision(class gaia::Actor* other);

};
