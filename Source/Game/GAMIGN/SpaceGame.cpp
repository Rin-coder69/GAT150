#include "SpaceGame.h"
#include "Framework/Scene.h"
#include "Core/Random.h"
#include "Math/Vector2.h"
#include "Render/Model.h"
#include "Render/Renderer.h"
#include "Input/InputSystem.h"
#include "Engine.h"
#include "Player.h"
#include "Enemy.h"
#include "gamedata.h"
#include "Core/Factory.h"
#include "Resources/ResourceManager.h"
#include "Render/particlesystem.h"
#include "Audio/AudioSystem.h"
#include "Rocket.h"
#include <fmod.hpp>
#include "Laser.h"
#include "Components/CircleCollider2d.h"
#include "../GamePCH.h"


#include <vector>
FMOD::System* m_audioSystem = nullptr;
FMOD::Sound* m_music = nullptr;
FMOD::Channel* m_musicChannel = nullptr;

bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<gaia::Scene>(this);

    gaia::json::document_t document;
    m_scene->Load("scene.json");
    //m_scene->
		// Initialize fonts
	//m_ttfFont = std::make_shared<gaia::Font>();
	//m_ttfFont->Load("ArcadeClassic.ttf", 128);

	//m_uiFont = std::make_shared<gaia::Font>();
	//m_uiFont->Load("ArcadeClassic.ttf", 48);


	m_scoreText = std::make_unique<gaia::Text>(gaia::Resources().GetWithID<gaia::Font>("ui_font","ArcadeClassic.ttf", 48.0f));
	m_livesText = std::make_unique<gaia::Text>(gaia::Resources().GetWithID<gaia::Font>("ui_font", "ArcadeClassic.ttf", 48.0f));
	m_titleText = std::make_unique<gaia::Text>(gaia::Resources().GetWithID<gaia::Font>("title_font", "ArcadeClassic.ttf", 128.0f));



    return true;
}

void SpaceGame::Update(float dt)
{
    switch (m_gameState)
    {
    case SpaceGame::GameState::Initialize:
        m_gameState = GameState::Title;
        break;

    case SpaceGame::GameState::Title:
        if (gaia::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_SPACE)) {
            m_gameState = GameState::StartGame;
        }
        break;

    case SpaceGame::GameState::StartGame:
        m_score = 0;
        m_lives = 3;
        m_enemySpawnTimer = 0;
        m_gameState = GameState::StartRound;
        break;

    case SpaceGame::GameState::StartRound:
    {   
        FMOD::System* audio;
		FMOD::System_Create(&audio);
        void* extradriverdata = nullptr;
        audio->init(32, FMOD_INIT_NORMAL, extradriverdata);
        FMOD::Sound* sound = nullptr;
		audio->createSound("wilnas.wav",FMOD_DEFAULT,0, &sound);
		audio->playSound(sound, nullptr, false, nullptr);
		audio->update();
		//m_scene->RemoveAllActors();

		auto player = gaia::Instantiate<gaia::Actor>("player");
		m_scene->AddActor(std::move(player));


        std::shared_ptr<gaia::Model> model = std::make_shared<gaia::Model>(GameData::shipPoints, gaia::vec3{ 0.0f, 0.4f, 0.2f });
        gaia::Transform transform{ gaia::vec2{ gaia::GetEngine().GetRenderer().GetWidth() * 0.5f, gaia::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 0.5};

        /*
		// Create the player actor
        auto player = std::make_unique<Player>(transform);
        player->speed = 1500.0f;
        player->rotationspeed = 180.0f;
        //player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";


		//components
		auto spriteRender = std::make_unique<gaia::SpriteRenderer>();
		spriteRender->textureName = "textures/Wilnas.png";
		player->AddComponent(std::move(spriteRender));

		auto rb = std::make_unique<gaia::RigidBody>();
        rb -> damping = 3.0f;
		player->AddComponent(std::move(rb));

		auto collider = std::make_unique<gaia::CircleCollider2d>();
        collider->radius = 60;
		player->AddComponent(std::move(collider));

        m_scene->AddActor(std::move(player));
          */
        m_gameState = GameState::Game;
    }
    break;
  
    case SpaceGame::GameState::Game:
		m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 2; // Reset enemy spawn timer
            SpawnEnemy();
        };
            
        break;

    case SpaceGame::GameState::PlayerDead:
		m_stateTimer -= dt;
        if (m_stateTimer <= 0) {
            m_lives--;
            if (m_lives == 0){ m_gameState = GameState::GameOver;
            if (m_musicChannel) {
                m_musicChannel->stop();
            }
            m_stateTimer = 3;}// Reset state timer
           
            else {
                // Reset the game state to start a new round
                m_gameState = GameState::StartRound;
            }
        
            /*m_gameState = GameState::Game;
            m_scene->RemoveAllActors();
            m_enemySpawnTimer = 0;*/
        }
        break;
    case SpaceGame::GameState::GameOver:
		m_stateTimer -= dt;
        if(m_stateTimer <= 0) {
            m_gameState = GameState::Title;
            m_scene->RemoveAllActors();
		}
        break;
    default:
        break;
    }
    m_scene->Update(gaia::GetEngine().GetTime().GetDeltaTime());
}


    void SpaceGame::Draw(gaia:: Renderer& renderer)
    {

        m_titleText->Create(gaia::GetEngine().GetRenderer(), "Gaia Space", gaia::vec3{ 1.0f, 1.0f, 1.0f });

		gaia::GetEngine().GetRenderer().SetColor(0.0f, 0.0f, 0.0f);
        m_titleText->Draw(gaia::GetEngine().GetRenderer(), 40.0f, 40.0f);
        m_scene->Draw(gaia::GetEngine().GetRenderer());

        if (m_gameState == GameState::GameOver) {
			m_titleText->Create(renderer, "Game Over", gaia::vec3{ 1.0f, 0.0f, 0.0f });
			m_titleText->Draw(renderer, 400, 400);
        }
		m_scoreText->Create(renderer, "Score: " + std::to_string(m_score), gaia::vec3{ 1.0f, 1.0f, 1.0f });
		m_scoreText->Draw(renderer, 20, 20);

        m_livesText->Create(renderer, "LIVES: " + std::to_string(m_lives), gaia::vec3{1, 1, 1});
        m_livesText->Draw(renderer,(float)(renderer.GetWidth()-200), (float)20);
		
        //m_scene->Draw(renderer);
		gaia::GetEngine().GetParticleSystem().Draw(renderer);
    }

    void SpaceGame::OnPlayerDeath()
    {
        m_gameState = GameState::PlayerDead;
		m_stateTimer = 2;
	}

    void SpaceGame::SpawnEnemy() {
        gaia::Actor* player = m_scene->GetActorByName<gaia::Actor>("player");
        if (player) {
            gaia::vec2 position = player->transform.position + gaia::random::onUnitCircle() * gaia::random::getReal(200.0f, 500.0f);
            gaia::Transform transform{ position, gaia::random::getReal(0.0f, 360.0f),0.2f };

            auto enemy = gaia::Instantiate("enemy", transform);
			
            //enemy->GetComponent<gaia::Transform>()->position = gaia::vec2{ gaia::random::getReal() * gaia::GetEngine().GetRenderer().GetWidth(), gaia::random::getReal() * gaia::GetEngine().GetRenderer().GetHeight() };
            m_scene->AddActor(std::move(enemy));
        }
    }

    void SpaceGame::ShutDown()
    {
        
    }

    