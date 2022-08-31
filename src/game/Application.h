#ifndef APPLICATION_H
#define APPLICATION_H

#include "SWDemo.h"
#include <engine/SDLWindow.h>
#include <engine/SDLRenderer.h>

#if defined(_WIN32)
#define WIN32_LEAN_AND_MEN
#include <windows.h>
#endif

class Application
{
public:

#if defined(_WIN32)
		struct Helper
		{
			static PCHAR* CommandLineToArgvA(PCHAR CmdLine, int* argc);
		};
#endif

	Application(int argc, char* args[]);
	int Run();

	void ShowDebugConsole();

private:

	void HandleWindowEvents();

	int argc;
	char** argv;
	SDLWindowPtr window;
	SDLRendererPtr renderer;
	GamePtr game;

	bool showDebugConsole;
};

#endif