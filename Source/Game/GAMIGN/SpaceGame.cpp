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
#include "Render/particlesystem.h"
#include "Audio/AudioSystem.h"
#include "Rocket.h"
#include <fmod.hpp>
#include "Laser.h"


#include <vector>
FMOD::System* m_audioSystem = nullptr;
FMOD::Sound* m_music = nullptr;
FMOD::Channel* m_musicChannel = nullptr;

bool SpaceGame::Initialize()
{
    m_scene = std::make_unique<gaia::Scene>(this);
		// Initialize fonts
	m_ttfFont = std::make_shared<gaia::Font>();
	m_ttfFont->Load("ArcadeClassic.ttf", 128);

	m_uiFont = std::make_shared<gaia::Font>();
	m_uiFont->Load("ArcadeClassic.ttf", 48);


	m_titleText = std::make_unique<gaia::Text>(m_ttfFont);
	m_scoreText = std::make_unique<gaia::Text>(m_uiFont);
	m_livesText = std::make_unique<gaia::Text>(m_uiFont);

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
		audio->createSound("8bit.wav",FMOD_DEFAULT,0, &sound);
		audio->playSound(sound, nullptr, false, nullptr);
		audio->update();
		m_scene->RemoveAllActors();
        std::shared_ptr<gaia::Model> model = std::make_shared<gaia::Model>(GameData::shipPoints, gaia::vec3{ 0.0f, 0.4f, 1.0f });
        gaia::Transform transform{ gaia::vec2{ gaia::GetEngine().GetRenderer().GetWidth() * 0.5f, gaia::GetEngine().GetRenderer().GetHeight() * 0.5f }, 0, 15};
        auto player = std::make_unique<Player>(transform, model);
        player->speed = 1500.0f;
        player->rotationspeed = 180.0f;
        player->damping = 1.5f;
        player->name = "player";
        player->tag = "player";

        m_scene->AddActor(std::move(player));
        m_gameState = GameState::Game;
    }
    break;
    case SpaceGame::GameState::Game:
		m_enemySpawnTimer -= dt;
        if (m_enemySpawnTimer <= 0) {
            m_enemySpawnTimer = 2; // Reset enemy spawn timer

            // create enemies
            std::shared_ptr<gaia::Model> enemyModel = std::make_shared<gaia::Model>(GameData::enemyPoints, gaia::vec3{1, 0, 0 });
            gaia::Transform transform{ gaia::vec2{ gaia::random::getReal() * gaia::GetEngine().GetRenderer().GetWidth() * 0.5f, gaia::random::getReal() * gaia::GetEngine().GetRenderer().GetHeight() }, 0, 10 };
            std::unique_ptr<Enemy> enemy = std::make_unique<Enemy>(transform, enemyModel);
            enemy->fireTime = 3;
			enemy->fireTimer = 5;
            enemy->damping = 0.2f;
            enemy->speed = (gaia::random::getReal()*200) + 300;//(gaia::random::getReal() * 800) + 500;
            enemy->tag = "enemy";
            m_scene->AddActor(std::move(enemy));
        }
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
		
        m_scene->Draw(renderer);
		gaia::GetEngine().GetParticleSystem().Draw(renderer);
    }

    void SpaceGame::OnPlayerDeath()
    {
        m_gameState = GameState::PlayerDead;
		m_stateTimer = 2;
	}

    void SpaceGame::ShutDown()
    {
        //
    }

    