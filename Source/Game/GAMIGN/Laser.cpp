#include "Laser.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Render/Renderer.h"
#include "Player.h"
#include "Render/ParticleSystem.h"
#include <Math/transform.h>
#include "Math/math.h"
#include "Math/vector2.h"
#include "Core/Random.h"



void Laser::Update(float dt)
{
	gaia::vec2 force = gaia::vec2{ 1,0 }.Rotate(gaia::math::degToRad(transform.rotation));
	velocity += (force * speed) * dt;

	transform.position.x = gaia::math::wrap(transform.position.x, 0.0f, (float)gaia::GetEngine().GetRenderer().GetWidth());
	transform.position.y = gaia::math::wrap(transform.position.y, 0.0f, (float)gaia::GetEngine().GetRenderer().GetHeight());


	Actor::Update(dt);
}


void Laser::OnCollision(Actor* other)
{
	std::cout << other->tag << std::endl;
	if (other->tag != tag) {
		destroyed = true;

	}
}