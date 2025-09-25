#include <Game/GameLogic.h>
#include <chrono>

int main()
{
	constexpr GLsizei windowWidth{ 800 };
	constexpr GLsizei windowHeight{ 800 };
	//this is temporary
	//TODO: replace this with window while loop
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GaspardEngine::LogManager Manager{};
	Manager.Init(L"Program manager");

	GLFWwindow* pWindow{ glfwCreateWindow(windowWidth,windowHeight,"GaspardEngine",NULL,NULL) };

	if (pWindow == NULL)
	{
		Manager.LogError(L"Cannot create GLFW window.");
		glfwTerminate();
		return -1;
	}

	GaspardEngine::Game Game{};
	Game.InitializeGame();

	glfwMakeContextCurrent(pWindow);

	gladLoadGL();

	glViewport(0, 0, windowWidth, windowHeight);

	std::chrono::high_resolution_clock::time_point start{ std::chrono::high_resolution_clock::now() };
	std::chrono::high_resolution_clock::time_point end{ };
	while (!glfwWindowShouldClose(pWindow))
	{
		end = std::chrono::high_resolution_clock::now();
		float deltaTime{ std::chrono::duration<float>(end - start).count() };
		start = std::chrono::high_resolution_clock::now();
		glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		Game.GameLogic(deltaTime);
		glfwSwapBuffers(pWindow);
		glfwPollEvents();
	}
	Game.Close();
	glfwDestroyWindow(pWindow);
	glfwTerminate();
	return 0;
}