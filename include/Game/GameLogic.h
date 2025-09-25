#pragma once

namespace GaspardEngine {
	class Game {
	public:
		void InitializeGame();
		void GameLogic(float deltaTime);
		void Close() noexcept;
	private:
		std::unique_ptr<LogManager> m_LogManager{};
	};
}