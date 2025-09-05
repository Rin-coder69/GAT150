#pragma once
#include "Components/Component.h"
#include "Math/vector2.h"



class plush : public gaia::Component
{
	float speed = 0;
	float maxSpeed = 100.0f;


	gaia::RigidBody* rigidBody{ nullptr };

public:
	plush() = default;
	Class_PROTOTYPE(plush)

	gaia::vec2* followpos;
	void Start() override;
	void Update(float deltaTime) override;
	void OnCollision(class gaia::Actor* other);
	void Read(const gaia::json::value_t& value) override;


};