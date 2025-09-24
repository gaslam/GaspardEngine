#include <Game/GameLogic.h>
int main()
{
	//this is temporary
	//TODO: replace this with window while loop
	bool testWhileLogic{ true };

	GaspardEngine::Game Game{};
	Game.InitializeGame();

	while (testWhileLogic)
	{
		Game.GameLogic(0.0f);
		testWhileLogic = false;
	}
	std::cin.ignore();
	Game.Close();
	return 0;
}