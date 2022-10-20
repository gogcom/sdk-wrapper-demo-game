#include "SWDemo.h"
#include <game/scenes/StartMenu.h>
#include <game/scenes/AchievementsView.h>
#include <game/scenes/StatsView.h>
#include <game/scenes/LeaderboardsView.h>
#include <game/scenes/FriendsView.h>
#include <game/scenes/LobbyMenuView.h>
#include <game/scenes/LobbyView.h>

#include <game/steam/StatsAndAchievementsData.h>

static std::string connectionString = "";

static bool ParseCmdLineArgs(int argc, char** argv)
{
	const std::string connectionStringPrefix = "+connect_";
	for (int i = 0; i < argc; ++i)
	{
		std::string cmdArg = argv[i];
		if (cmdArg.find(connectionStringPrefix) != std::string::npos)
		{
			connectionString = cmdArg;
			return true;
		}
	}
	return false;
}

extern "C" void __cdecl SteamAPIDebugTextHook(int nSeverity, const char *pchDebugText)
{
	printf(pchDebugText);

	if (nSeverity >= 1)
	{
		int x = 3;
		(void)x;
	}
}

SWDemo::SWDemo(const SDLRendererPtr& _renderer)
	: renderer{_renderer}
	, closeRequested{false}
	, isLoggedIn{false}
{
}

bool SWDemo::Init(int argc, char** argv)
{
	ParseCmdLineArgs(argc, argv);
	
	if (SteamAPI_RestartAppIfNecessary(k_uAppIdInvalid))
	{
		return EXIT_FAILURE;
	}

	if (!SteamAPI_Init())
	{
		printf("SteamAPI_Init() failed\n");
		printf("Fatal Error: Steam must be running to play this game (SteamAPI_Init() failed).\n");
		return EXIT_FAILURE;
		
		SteamClient()->SetWarningMessageHook( &SteamAPIDebugTextHook );
	}

	if (!SteamUser()->BLoggedOn())
	{
		printf("Steam user is not logged in\n");
		printf("Fatal Error: Steam user must be logged in to play this game (SteamUser()->BLoggedOn() returned false).\n");
		return EXIT_FAILURE;
	}

	isLoggedIn = true;

	userName = SteamFriends()->GetPersonaName();

	// TODO: to implement in IUtils
	// CSteamID steamID = SteamUser()->GetSteamID();
	// SteamFriends()->RequestUserInformation(steamID, false);
	// int avatarID = SteamFriends()->GetMediumFriendAvatar(steamID);
	// SteamUtils()->GetImageRGBA(int iIMage, unit8* pubDest, int nDestBufferSize);

	statsAndAchievements = std::make_shared<CStatsAndAchievements>(g_rgAchievements, 3, g_Stats, 4);
	leaderboards = std::make_shared<CLeaderboards>();
	friends = std::make_shared<CFriends>();

	SetGameState(GameState::State::START_MENU);

	return true;
}

void SWDemo::Close()
{
	closeRequested = true;
}

bool SWDemo::Release()
{
	SteamAPI_Shutdown();
	return true;
}

bool SWDemo::IsRunning() const
{
	return !closeRequested;
}

bool SWDemo::Update()
{
	if (gameState && gameState->Update() && !stateChanged)
			gameState->Render(renderer, userName, isLoggedIn);

	SteamAPI_RunCallbacks();
	SDL_Delay(30);

	if (stateChanged)
	{
		switch (currentGameState)
		{
			case GameState::State::START_MENU:
				gameState = std::make_shared<StartMenu>(shared_from_this());
				break;
			case GameState::State::ACHIEVEMENTS_VIEW:
				gameState = std::make_shared<AchievementsView>(shared_from_this(), statsAndAchievements);
				break;
			case GameState::State::STATS_VIEW:
				gameState = std::make_shared<StatsView>(shared_from_this(), statsAndAchievements);
				break;
			case GameState::State::LEADERBOARDS_VIEW:
				gameState = std::make_shared<LeaderboardsView>(shared_from_this(), leaderboards);
				break;
			case GameState::State::FRIENDS_VIEW:
				gameState = std::make_shared<FriendsView>(shared_from_this(), friends);
				break;
			case GameState::State::LOBBY_MENU_VIEW:
				gameState = std::make_shared<LobbyMenuView>(shared_from_this());
				break;
			case GameState::State::LOBBY_VIEW:
				gameState = std::make_shared<LobbyView>(shared_from_this(), lobby);
				break;
		}

		if (!gameState->Init())
			return false;

		stateChanged = false;
	}

	return true;
}

void SWDemo::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	if (!gameState)
		return;

	gameState->OnMouseDown(x, y);
}

void SWDemo::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	if (!gameState)
		return;

	gameState->OnMouseMotion(x, y);
}

void SWDemo::OnKeyDown(SDL_Keysym key)
{
	if (key.sym == SDLK_ESCAPE)
		Close();
	if (!gameState)
		return;
	gameState->OnKeyDown(key);
}

void SWDemo::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
	if (!gameState)
		return;

	gameState->OnMouseWheel(mouseWheel);
}

void SWDemo::OnTextInput(SDL_TextInputEvent inputEvent)
{
	if (!gameState)
		return;

	gameState->OnTextInput(inputEvent);
}

void SWDemo::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
	if (!gameState)
		return;

	gameState->OnTextEditing(editingEvent);
}

bool SWDemo::SetGameState(const GameState::State& state)
{
	if (gameState)
		gameState->Release();

	currentGameState = state;
	stateChanged = true;
	return true;
}

void SWDemo::SetLobby(const LobbyPtr& _lobby)
{
	lobby = _lobby;
}

void SWDemo::CreateLobby()
{
	lobby = std::make_shared<CLobby>(shared_from_this(), true, "");
}

void SWDemo::JoinLobby(const std::string& connectionString)
{
	SDL_Log("Joining lobby: %s", connectionString.c_str());
	lobby = std::make_shared<CLobby>(shared_from_this(), false, connectionString);
}

void SWDemo::LeaveLobby()
{
	lobby.reset();
}