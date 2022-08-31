#define SDL_MAIN_HANDLED
#include <game/Application.h>

int main(int argc, char* args[])
{
	Application app(argc, args);
	return app.Run();
}

#if defined(_WIN32)

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	int argc;
	LPSTR* argv = Application::Helper::CommandLineToArgvA(lpCmdLine, &argc);
	Application app(argc, argv);
	return app.Run();
}

#else

int main(int argc, char** argv)
{
	Application app(argc, argv);
	return app.Run();
}

#endif