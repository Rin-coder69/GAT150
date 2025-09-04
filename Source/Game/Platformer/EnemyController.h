#pragma once
#include "Components/Component.h"



class EnemyController : public gaia::Component
{
public:
	float speed = 0;
	float maxSpeed = 100.0f;
	float jump = 0;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;

	gaia::RigidBody* RigidBody{ nullptr };

public:
	EnemyController() = default;
	/*Player(const gaia::Transform& transform) :
		Actor{ transform }
	{}*/
	Class_PROTOTYPE(EnemyController)
		void Start() override;
	void Update(float deltaTime) override;
	void OnCollision(class gaia::Actor* other);
	void Read(const gaia::json::value_t& value) override;

};