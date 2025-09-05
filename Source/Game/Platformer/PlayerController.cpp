#include "PlayerController.h"
#include "../GamePCH.h"

 FACTORY_REGISTER(PlayerController);

	void PlayerController::Start() {
		rigidBody = owner->GetComponent<gaia::RigidBody>();
	}


    void PlayerController::Update(float deltaTime)
    {
        if (!rigidBody) return; // prevent crash if component missing

        float dir = 0;
        if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) {
            dir = -1;
            gaia::Logger::Info("Key A is pressed");
            std::cout << "AAAA" << std::endl;
        }
        if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) dir = +1;
		gaia::Logger::Info("Key D is pressed");

        // Apply horizontal force using "speed" from JSON
        if (dir != 0) {
            rigidBody->ApplyForce(gaia::vec2{ 1, 0 } * dir * 10000);
           
        }

        // Jump with "jump" from JSON
        if (gaia::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            rigidBody->ApplyForce(gaia::vec2{ 0, -1 } * jump*500);
        }

        // Limit horizontal velocity to maxSpeed (if set in JSON)
       /* auto vel = RigidBody->GetVelocity();
        if (std::abs(vel.x) > maxSpeed) {
            vel.x = (vel.x > 0) ? maxSpeed : -maxSpeed;
            RigidBody->SetVelocity(vel);
        }*/
    }

	

	void PlayerController::OnCollision(class gaia::Actor * other)
	{
        if (owner->tag != other->tag) {
            owner->destroyed = true;
            //owner->scene->GetGame()->AddPoints(100);
        }
	}

	void PlayerController::Read(const gaia::json::value_t & value)
	{
		Object::Read(value);
		JSON_READ(value, maxSpeed);
		JSON_READ(value, speed);
		JSON_READ(value, fireTime);
		JSON_READ(value, jump);

	}

