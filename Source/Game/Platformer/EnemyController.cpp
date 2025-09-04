#include "EnemyController.h"
#include "../GamePCH.h"

 FACTORY_REGISTER(EnemyController);

void EnemyController::Start() {
	RigidBody = owner->GetComponent<gaia::RigidBody>();
}


void EnemyController::Update(float deltaTime)
{
	float dir = 0;
	auto player = owner->scene->GetActorByName<gaia::Actor>("platformplayer");
	if (player) {
		if (player->transform.position.x < owner->transform.position.x) dir = -1;
		else dir = +1;
	}


	if (dir != 0) {
		RigidBody->ApplyForce(gaia::vec2{ 1,0 } * dir * 500);

	}

}


void EnemyController::OnCollision(class gaia::Actor* other)
{
}

void EnemyController::Read(const gaia::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, speed);
	JSON_READ(value, fireTime);
	JSON_READ(value, jump);

}
