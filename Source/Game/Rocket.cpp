#include "Rocket.h"	
#include "Engine.h"
#include "Framework/Scene.h"
#include "Render/Renderer.h"
#include "../Game/GAMIGN/Player.h"


void Rocket::Update(float dt)
{
	gaia::vec2 force = gaia::vec2{ 1,0 }.Rotate(gaia::math::degToRad(transform.rotation)) * velocity += force;

	transform.position.x = gaia::math::wrap(transform.position.x, 0.0f, (float)gaia::GetEngine().GetRenderer().GetWidth());
	transform.position.y = gaia::math::wrap(transform.position.y, 0.0f, (float)gaia::GetEngine().GetRenderer().GetHeight());

		Actor::Update(dt);
}


void Rocket::OnCollision(Actor* other)
{
	if (other->tag != tag) {
		destroyed = true;

	}
}
