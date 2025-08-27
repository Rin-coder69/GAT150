#pragma once
#include "Components/Component.h"


class Player : public gaia::Component {
	enum class WeaponType { Rocket, Laser };
	WeaponType currentWeapon = WeaponType::Rocket;


public:
	float speed = 200;
	float rotationspeed = 100.0f;
	float fireTime = 0.2f;
	float fireTimer = 0.0f;
public:
	Player() = default;
	/*Player(const gaia::Transform& transform) :
		Actor{ transform }
	{}*/

	void Update(float deltaTime) override;


	void OnCollision(class gaia::Actor* other);

	void Read(const gaia::json::value_t& value) override;

};