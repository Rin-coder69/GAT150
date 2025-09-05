#include "plush.h"
#include "PlayerController.h"
#include "..\GamePCH.h"

FACTORY_REGISTER(plush);

void plush::Start() {
	rigidBody = owner->GetComponent<gaia::RigidBody>();
}

void plush::Update(float deltaTime)
{

	}





void plush::OnCollision(class gaia::Actor* other)
{
	if (gaia::tolower(other->tag),"plush")
	owner->destroyed = true;
	
		//owner->scene->GetGame()->AddPoints(100);

}

//make sure its the player. set th follow pos to the player position
void plush::Read(const gaia::json::value_t& value)
{
	Object::Read(value);
	JSON_READ(value, maxSpeed);
	JSON_READ(value, speed);

}