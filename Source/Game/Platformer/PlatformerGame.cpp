#include "PlatformerGame.h"
#include "..\GamePCH.h"
bool PlatformerGame::Initialize() {
	OBSERVER_ADD(player_dead);
	OBSERVER_ADD(add_points);
	m_scene = std::make_unique<gaia::Scene>(this);
	m_scene->Load("scenes/prototypes.json");
	m_scene->Load("scenes/level.json");
	return true;

}
void PlatformerGame::ShutDown() {
	//
}

void PlatformerGame::Update(float dt) {
	switch (m_gameState) {
	case PlatformerGame::GameState::Initialize:
		m_gameState = GameState::StartRound;
		break;
	case PlatformerGame::GameState::Title:
		break;
	case PlatformerGame::GameState::StartGame:
		break;
	case PlatformerGame::GameState::StartRound:
		SpawnPlayer();
		SpawnEnemy();
		
		m_gameState = GameState::Game;
		break;
	case PlatformerGame::GameState::Game:
		break;
	case PlatformerGame::GameState::PlayerDead:
		break;
	case PlatformerGame::GameState::GameOver:
		break;
	default:
		break;
	}
	m_scene->Update(gaia::GetEngine().GetTime().GetDeltaTime());

}
void PlatformerGame::Draw(class gaia::Renderer& renderer){
	m_scene->Draw(renderer);
	gaia::GetEngine().GetParticleSystem().Draw(renderer);
}
void PlatformerGame::OnNotify(const gaia::Event& event) {

}

void PlatformerGame::SpawnPlayer()
{
	auto player = gaia::Instantiate("platformplayer");
	//player->transform.position = gaia::vec2{ gaia::random::getReal(0.0f,1080.0f), gaia::random::getReal(0.0f,100.0f)};
	m_scene->AddActor(std::move(player));

	/*auto bat = gaia::Instantiate("bat");
	m_scene->AddActor(std::move(bat));*/
	
}

void PlatformerGame::SpawnEnemy() {
	auto enemy = gaia::Instantiate("platformenemy");
	//player->transform.position = gaia::vec2{ gaia::random::getReal(0.0f,1080.0f), gaia::random::getReal(0.0f,100.0f)};
	m_scene->AddActor(std::move(enemy));
	}