#include "Enemy.h"
#include "Engine.h"
#include "Framework/Scene.h"
#include "Framework/game.h"
#include "Render/Renderer.h"
#include "Player.h"
#include "math/vector3.h"
#include "Rocket.h"
#include "gamedata.h"
#include "Render/Model.h"
#include "Render/particlesystem.h"
#include "Core/random.h"

void Enemy::Update(float deltaTime)
{

	Player* player = scene->GetActorByName<Player>("player");
	if (player) {
		gaia::vec2 direction{ 0,0 };
		direction = player->transform.position - transform.position;
		direction = direction.Normalized();
		transform.rotation = gaia::math::radToDeg(direction.Angle());
	}
	gaia::vec2 force = gaia::vec2{ 1,0 }.Rotate(gaia::math::degToRad(transform.rotation));
	velocity += (force * speed) * deltaTime;

	transform.position.x = gaia::math::wrap(transform.position.x, 0.0f, (float)gaia::GetEngine().GetRenderer().GetWidth());
	transform.position.y = gaia::math::wrap(transform.position.y, 0.0f, (float)gaia::GetEngine().GetRenderer().GetHeight());

	fireTimer -= deltaTime;
	if (fireTimer <= 0) {
		fireTimer = fireTime;

		std::shared_ptr<gaia::Model> model = std::make_shared<gaia::Model>(GameData::shipPoints, gaia::vec3{ 0.0f,1.0f,0.0f });
		gaia::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
		auto rocket = std::make_unique<Rocket>(transform, model);
		rocket->speed = 2.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "enemy";
		rocket->tag = "enemy";

		scene->AddActor(std::move(rocket));
	}

	Actor::Update(deltaTime);
}

void Enemy::OnCollision(Actor* other)
{
	if (tag != other->tag) {
		destroyed = true;
		scene->GetGame()->AddPoints(100);
		//game->AddPoints(100);
		for(int i = 0; i < 100; i++) {
			gaia::Particle particle;
			particle.position = transform.position;
			particle.velocity = gaia::vec2{ gaia::random::getReal(-200.0f, 200.0f), gaia::random::getReal(-200.0f, 200.0f) };
			particle.color = gaia::vec3{ 1, 1, 1 };
			particle.lifespan = 2.0f;
			gaia::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}

