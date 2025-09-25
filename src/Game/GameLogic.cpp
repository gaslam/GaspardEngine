#include "Game/GameLogic.h"
#include <format>

namespace GaspardEngine {

	void Game::InitializeGame() {
		m_LogManager = std::make_unique<LogManager>();
		m_LogManager->Init(L"GameLogger");
	};
	void Game::GameLogic(float deltaTime) {
		auto test{ std::format(L"deltaTime {}", deltaTime) };
		m_LogManager->LogInfo(test.c_str());
	};
	void Game::Close() noexcept
	{

	};
}