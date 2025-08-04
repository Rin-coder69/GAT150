#include "Player.h"
#include "Rocket.h"
#include "../engine/Engine.h"
#include "Input/InputSystem.h"
#include "Framework/Scene.h"
#include "Math/math.h"
#include "Math/vector3.h"
#include "Render/Model.h"
#include "Render/Renderer.h"
#include "gamedata.h"
#include "SpaceGame.h"
#include "gamedata.h"
#include "Audio/AudioSystem.h"
#include "Render/particlesystem.h"
#include "Core/Random.h"
#include "Laser.h"


void Player::Update(float deltaTime) {
    // Switch weapon with TAB key
    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_TAB)) {
        if (currentWeapon == WeaponType::Rocket) currentWeapon = WeaponType::Laser;
        else currentWeapon = WeaponType::Rocket;
    }

    gaia::Particle particle;
	particle.position = transform.position;
    particle.velocity = gaia::vec2{ gaia::random::getReal(-200.0f,200.0f),gaia::random::getReal(-200.0f,200.0f) };
	particle.color = gaia::vec3{ 1,1,1 };
	particle.lifespan = 2.0f;
	//gaia::GetEngine().GetParticleSystem().AddParticle(particle);
    //rotation
    float thrust = 0;
    float rotate = 0;

    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) rotate = -1;
    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) rotate = +1;


    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) thrust = -1;
    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) thrust = +1;



    transform.rotation += (rotate * rotationspeed) * deltaTime;
    gaia::vec2 direction{ 1,0 };
    gaia::vec2 force = direction.Rotate(gaia::math::degToRad(transform.rotation)) * thrust * speed;
    velocity += force * deltaTime;


    transform.position.x = gaia::math::wrap(transform.position.x, 0.0f, (float)gaia::GetEngine().GetRenderer().GetWidth());
    transform.position.y = gaia::math::wrap(transform.position.y, 0.0f, (float)gaia::GetEngine().GetRenderer().GetHeight());

 

    fireTimer -= deltaTime;
    if (gaia::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_SPACE) && fireTimer <= 0) {
        fireTimer = fireTime;
        gaia::Transform transform{ this->transform.position, this->transform.rotation, 2.0f };
        std::shared_ptr<gaia::Model> model;

        switch (currentWeapon) {
        case WeaponType::Rocket:
            model = std::make_shared<gaia::Model>(GameData::shipPoints, gaia::vec3{ 1.0f, 1.4f, 1.0f });
            {
                auto rocket = std::make_unique<Rocket>(transform, model);
                rocket->speed = 1500.0f;
                rocket->lifespan = 1.5f;
                rocket->damping = 1.5f;
                rocket->name = "player";
                rocket->tag = "player";
                scene->AddActor(std::move(rocket));
                gaia::GetEngine().GetAudio().PlaySound("cowbell.wav");
            }
            break;

        case WeaponType::Laser:
            model = std::make_shared<gaia::Model>(GameData::enemyPoints, gaia::vec3{ 0.5f, 2.0f, 2.0f });
            {
                auto laser = std::make_unique<Laser>(transform, model);
                laser->speed = 2000.0f;
                laser->lifespan = 0.8f;
                laser->damping = 1.0f;
                laser->name = "laser";
                laser->tag = "player";
                scene->AddActor(std::move(laser));
                gaia::GetEngine().GetAudio().PlaySound("Laser.wav"); // add a laser sound too
            }
            break;
        }
    }


    Actor::Update(deltaTime);
}

void Player::OnCollision(Actor* other)
{   
    if (other->tag != tag) {

    destroyed = true;
    dynamic_cast<SpaceGame*>(scene->GetGame())->OnPlayerDeath();
				//scene->GetGame()->AddPoints(100);
    }
	std::cout << other->tag << std::endl;
}
  

