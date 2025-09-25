#include <Game/GameLogic.h>
#include <chrono>

int main()
{
#ifdef _WIN32
#ifdef _MSC_VER 
#if PRODUCTION_BUILD == 0

	FILE* fpstdin = nullptr;
	FILE* fpstdout = nullptr;
	FILE* fpstderr = nullptr;
	AllocConsole();
	(void)freopen_s(&fpstdin,"conin$", "r", stdin);
	(void)freopen_s(&fpstdout,"conout$", "w", stdout);
	(void)freopen_s(&fpstderr,"conout$", "w", stderr);
	std::cout.sync_with_stdio();
#endif
#endif
#endif
	constexpr GLsizei windowWidth{ 800 };
	constexpr GLsizei windowHeight{ 800 };
	//this is temporary
	//TODO: replace this with window while loop
	glfwInit();
	glfwWindowHint(GLFW_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_VERSION_MINOR, 3);

	GLFWwindow* pWindow{ glfwCreateWindow(windowWidth,windowHeight,"GaspardEngine",NULL,NULL) };

	if (pWindow == NULL)
	{
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