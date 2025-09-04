#include "plush.h"
#include "PlayerController.h"
#include "../GamePCH.h"

FACTORY_REGISTER(plush);

void plush::Start() {
	rigidBody = owner->GetComponent<gaia::RigidBody>();
}


/*void plush::OnCollision(class gaia::Actor* other)
{
	if(other->GetComponent<PlayerController>()){
		owner->GetComponent
	}
}*/
//make sure its the player. set th follow pos to the player position
void plush::Read(const gaia::json::value_t& value)
{
	Object::Read(value);
	

}