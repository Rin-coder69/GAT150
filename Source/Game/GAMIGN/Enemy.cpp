#include "Enemy.h"
#include "Player.h"
#include "Rocket.h"
#include "gamedata.h"
#include "../GamePCH.h"
FACTORY_REGISTER(Enemy)

void Enemy::Update(float deltaTime)
{
	/*
	bool playerSeen = false;
	Actor* player = owner->scene->GetActorByName<Actor>("player");
	if (player) {
		gaia::vec2 direction{ 0,0 };
		direction = player->transform.position - owner->transform.position;
		direction = direction.Normalized();
		owner->transform.rotation = gaia::math::radToDeg(direction.Angle());
	}
	gaia::vec2 force = gaia::vec2{ 1,0 }.Rotate(gaia::math::degToRad(owner->transform.rotation));
	//velocity += (force * speed) * deltaTime;
	auto rb = owner->GetComponent<gaia::RigidBody>();
	if (rb)
	{
		rb->velocity += force * deltaTime;
	}

	owner->transform.position.x = gaia::math::wrap(owner->transform.position.x, 0.0f, (float)gaia::GetEngine().GetRenderer().GetWidth());
	owner->transform.position.y = gaia::math::wrap(owner->transform.position.y, 0.0f, (float)gaia::GetEngine().GetRenderer().GetHeight());

	fireTimer -= deltaTime;
	if (fireTimer <= 0) {
		fireTimer = fireTime;

		//std::shared_ptr<gaia::Model> model = std::make_shared<gaia::Model>(GameData::shipPoints, gaia::vec3{ 0.0f,1.0f,0.0f });
		gaia::Transform transform{ owner->transform.position, owner->transform.rotation, 2.0f };
		auto rocket = std::make_unique<Actor>(transform); //gaia::Resources().Get<gaia::Texture>("textures/blue_01.png", gaia::GetEngine().GetRenderer()));
		rocket->speed = 2.0f;
		rocket->lifespan = 1.5f;
		rocket->name = "enemy";
		rocket->tag = "enemy";
		//components
		auto spriteRender = std::make_unique<gaia::SpriteRenderer>();
		spriteRender->textureName = "textures/blue_01.png";
		rocket -> AddComponent(std::move(spriteRender));

		auto rb = std::make_unique<gaia::RigidBody>();
	
		player->AddComponent(std::move(rb));

		scene->AddActor(std::move(rocket));
	}

	Actor::Update(deltaTime);
	*/
}

void Enemy::OnCollision(gaia::Actor* other)
{
	if (owner->tag != other->tag) {
		owner->destroyed = true;
		owner->scene->GetGame()->AddPoints(100);
		//game->AddPoints(100);
		for(int i = 0; i < 100; i++) {
			gaia::Particle particle;
			particle.position = owner->transform.position;
			particle.velocity = gaia::vec2{ gaia::random::getReal(-200.0f, 200.0f), gaia::random::getReal(-200.0f, 200.0f) };
			particle.color = gaia::vec3{ 1, 1, 1 };
			particle.lifespan = 2.0f;
			gaia::GetEngine().GetParticleSystem().AddParticle(particle);
		}
	}
}

