#pragma once
#include "Framework/Game.h"
#include "Render/Font.h"
#include "Render/Text.h"
#include <SDL3_ttf/SDL_ttf.h>
class SpaceGame : public gaia::Game {
public:
	enum class GameState {
		Initialize,
		Title,
		StartGame,
		StartRound,
		Game,
		PlayerDead,
		GameOver,
	};
	SpaceGame() = default;

	bool Initialize() override;
	void ShutDown() override;

	void Update(float dt) override;
	void Draw(class gaia::Renderer& renderer) override ;

	void OnPlayerDeath();
private:
	friend class Text;
	GameState m_gameState = GameState::Initialize;
	float m_enemySpawnTimer{ 0 };
	float m_stateTimer{ 0 };
	std::shared_ptr<class gaia::Font> m_ttfFont;
	std::shared_ptr<class gaia::Font> m_uiFont;


	std::shared_ptr<class gaia::Text> m_titleText;
	std::shared_ptr<class gaia::Text> m_scoreText;
	std::shared_ptr<class gaia::Text> m_livesText;


};

