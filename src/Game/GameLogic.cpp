#include "Game/GameLogic.h"

namespace GaspardEngine {

	void Game::InitializeGame() {
		m_LogManager = std::make_unique<LogManager>();
		m_LogManager->Init(L"GameLogger");
	};
	void Game::GameLogic(float) {
	};
	void Game::Close() noexcept
	{

	};
}