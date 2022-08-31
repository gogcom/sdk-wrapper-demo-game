#include "Application.h"
#include <SDL.h>
#include <SDL_syswm.h>

#include <stdio.h>
#include <iostream>
#include <cstdio>
#include <io.h>
#include <fcntl.h>

#if defined(_WIN32)
#include <shellapi.h>
#endif

#if defined(_WIN32)
PCHAR* Application::Helper::CommandLineToArgvA(PCHAR CmdLine, int* _argc)
{
	PCHAR* argv;
	PCHAR  _argv;
	ULONG   len;
	ULONG   argc;
	CHAR   a;
	ULONG   i, j;

	BOOLEAN  in_QM;
	BOOLEAN  in_TEXT;
	BOOLEAN  in_SPACE;

	len = strlen(CmdLine);
	i = ((len + 2) / 2) * sizeof(PVOID) + sizeof(PVOID);

	argv = (PCHAR*)GlobalAlloc(GMEM_FIXED,
		i + (len + 2) * sizeof(CHAR));

	_argv = (PCHAR)(((PUCHAR)argv) + i);

	argc = 0;
	argv[argc] = _argv;
	in_QM = FALSE;
	in_TEXT = FALSE;
	in_SPACE = TRUE;
	i = 0;
	j = 0;

	while (a = CmdLine[i])
	{
		if (in_QM)
		{
			if (a == '\"')
			{
				in_QM = FALSE;
			}
			else
			{
				_argv[j] = a;
				j++;
			}
		}
		else
		{
			switch (a)
			{
				case '\"':
					in_QM = TRUE;
					in_TEXT = TRUE;
					if (in_SPACE)
					{
						argv[argc] = _argv + j;
						argc++;
					}
					in_SPACE = FALSE;
					break;
				case ' ':
				case '\t':
				case '\n':
				case '\r':
					if (in_TEXT)
					{
						_argv[j] = '\0';
						j++;
					}
					in_TEXT = FALSE;
					in_SPACE = TRUE;
					break;
				default:
					in_TEXT = TRUE;
					if (in_SPACE)
					{
						argv[argc] = _argv + j;
						argc++;
					}
					_argv[j] = a;
					j++;
					in_SPACE = FALSE;
					break;
			}
		}
		i++;
	}
	_argv[j] = '\0';
	argv[argc] = NULL;

	(*_argc) = argc;
	return argv;
}
#endif

Application::Application(int _argc, char** _argv)
	: argc(_argc)
	, argv(_argv)
	, window(std::make_shared<SDLWindow>("SWGame Demo", 1280, 720))
	, renderer(std::make_shared<SDLRenderer>(window))
	, game(std::make_shared<SWDemo>(renderer))
	, showDebugConsole{false}
{
}

int Application::Run()
{
	FreeConsole();

	if (!window->Init())
		return -1;

	if (!renderer->Init())
		return -2;

	if (!game->Init(argc, argv))
		return -3;

	while (game->IsRunning())
	{
		HandleWindowEvents();
		game->Update();
	}

	game->Release();

	renderer->Release();

	window->Release();

	SDL_Quit();

	return 0;
}

void Application::HandleWindowEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		if (event.type == SDL_QUIT)
		{
			game->Close();
			break;
		}
		else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_p)
		{
			ShowDebugConsole();
		}
		else if (event.type == SDL_MOUSEBUTTONDOWN)
		{
			game->OnMouseDown(event.button.x, event.button.y);
		}
		else if (event.type == SDL_MOUSEMOTION)
		{
			game->OnMouseMotion(event.motion.x, event.motion.y);
		}
		else if (event.type == SDL_KEYDOWN)
		{
			game->OnKeyDown(event.key.keysym);
		}
		else if (event.type == SDL_MOUSEWHEEL)
		{
			game->OnMouseWheel(event.wheel);
		}
		// else if (event.type == SDL_TEXTINPUT)
		// {
		// 	game->OnTextInput(event.text);
		// }
		// else if (event.type == SDL_TEXTEDITING)
		// {
		// 	game->OnTextEditing(event.edit);
		// }
	}
}

void Application::ShowDebugConsole()
{
	if (!showDebugConsole)
	{
		showDebugConsole == true;

		// AllocConsole();

		// HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
		// int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
		// FILE* hf_out = _fdopen(hCrt, "w");
		// setvbuf(hf_out, NULL, _IONBF, 1);
		// *stdout = *hf_out;

		// HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
		// hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
		// FILE* hf_in = _fdopen(hCrt, "r");
		// setvbuf(hf_in, NULL, _IONBF, 128);
		// *stdin = *hf_in;

	int hConHandle;
    intptr_t lStdHandle;
    CONSOLE_SCREEN_BUFFER_INFO coninfo;
    FILE *fp;

    // allocate a console for this app
    AllocConsole();

    // set the screen buffer to be big enough to let us scroll text
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &coninfo);
    coninfo.dwSize.Y = 500;
    SetConsoleScreenBufferSize(GetStdHandle(STD_OUTPUT_HANDLE), coninfo.dwSize);

    // redirect unbuffered STDOUT to the console
    lStdHandle = (intptr_t)GetStdHandle(STD_OUTPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stdout = *fp;
    setvbuf( stdout, NULL, _IONBF, 0 );

    // redirect unbuffered STDIN to the console
    lStdHandle = (intptr_t)GetStdHandle(STD_INPUT_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "r" );
    *stdin = *fp;
    setvbuf( stdin, NULL, _IONBF, 0 );

    // redirect unbuffered STDERR to the console
    lStdHandle = (intptr_t)GetStdHandle(STD_ERROR_HANDLE);
    hConHandle = _open_osfhandle(lStdHandle, _O_TEXT);
    fp = _fdopen( hConHandle, "w" );
    *stderr = *fp;
    setvbuf( stderr, NULL, _IONBF, 0 );

    // make cout, wcout, cin, wcin, wcerr, cerr, wclog and clog point to console as well
    std::ios::sync_with_stdio();

	SDL_SysWMinfo wmInfo;
	SDL_VERSION(&wmInfo.version);
	SDL_GetWindowWMInfo(window->GetHandle(), &wmInfo);
	HWND hwnd = wmInfo.info.win.window;

    //Keep our window in focus
    SetForegroundWindow(hwnd);                        // Slightly Higher Priority
    SetFocus(hwnd);                                   // Sets Keyboard Focus To The Window

		printf("SHOW DEBUG CONSOLE");
	}
	else
	{
		printf("HIDE DEBUG CONSOLE");
		showDebugConsole == false;
		FreeConsole();
	}
}
