#include "PlayerController.h"
#include "../GamePCH.h"

 FACTORY_REGISTER(PlayerController);

	void PlayerController::Start() {
		RigidBody = owner->GetComponent<gaia::RigidBody>();
	}


	void PlayerController::Update(float deltaTime)
	{
		float dir = 0;
		if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) dir = -1;
		if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;

		if (dir != 0) {
			RigidBody->ApplyForce(gaia::vec2{ 1,0 } *dir * 1000);

		}
		if(gaia::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)){
			RigidBody->ApplyForce(gaia::vec2{0,-1 } * 10000);
		}
	}
	

	void PlayerController::OnCollision(class gaia::Actor * other)
	{
	}

	void PlayerController::Read(const gaia::json::value_t & value)
	{
		Object::Read(value);
		JSON_READ(value, maxSpeed);
		JSON_READ(value, speed);
		JSON_READ(value, fireTime);
		JSON_READ(value, jump);

	}

