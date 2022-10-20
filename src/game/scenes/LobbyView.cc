#include "LobbyView.h"
#include <game/SWDemo.h>

constexpr auto BUTTON_HEIGHT = 50;
constexpr auto PADDING = BUTTON_HEIGHT + 15;

inline std::shared_ptr<Button> MakeButton(std::string label, int offsetX, int offsetY, GUIAction action)
{
    return std::make_shared<Button>(std::move(label), offsetX, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

inline std::shared_ptr<TextInput> MakeTextInput(std::string label, int offsetX, int offsetY, GUIAction action)
{
    return std::make_shared<TextInput>(std::move(label), offsetX, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

inline std::shared_ptr<TextOutputDisplay> MakeTextOutputDisplay(std::string label, int x, int y, int w, int h, GUIAction action)
{
    return std::make_shared<TextOutputDisplay>(std::move(label), x, y, w, h, std::move(action));
}

// TODO: Make all interface pointers unique and move them to Game class
LobbyView::LobbyView(const GamePtr& _game, const LobbyPtr& _lobby)
    : GameState(_game)
    , lobby(_lobby)
{
}

bool LobbyView::Init()
{
	std::string lobbyIDstr {std::to_string(lobby->GetLobbyID().ConvertToUint64())};
	std::string lobbyInitString{"Lobby View"};
	textOutputDisplay = MakeTextOutputDisplay("LOBBY VIEW TEXT OUTPUT", 400, 150, 800, 400,
		[&]()
		{
			printf("Lobby View Text Output\n");textOutputDisplay->SetDisplayText(lobbyInitString);
		});
	textOutputDisplay->SetDisplayText(lobbyInitString);

	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Main Menu\n");game->SetGameState(GameState::State::START_MENU);
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("BACK", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Back to lobby menu\n");game->SetGameState(GameState::State::LOBBY_MENU_VIEW);
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton(lobbyIDstr, offsetX, offsetY,
		[&]()
		{
			SDL_Log("%s", std::to_string(lobby->GetLobbyID().ConvertToUint64()).c_str());
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("INVITE THROUGH OVERLAY", offsetX, offsetY,
		[&]()
		{
			SteamFriends()->ActivateGameOverlayInviteDialogConnectString(lobby->GetConnectionString().c_str());
		}));
	// For testing purposes
	// buttons.emplace_back(MakeButton("SEND INVITATION", offsetX, offsetY,
	// 	[&, _offsetX = offsetX, _offsetY = offsetY]()
	// 	{
	// 		if(!textInput)
	// 		{
	// 			textInput = MakeTextInput("Enter friend's name", _offsetX, _offsetY + PADDING, [&]()
	// 				{
	// 					galaxy::api::Friends()->FindUser(textInput->ReturnInputText().c_str());
	// 					SteamMatchmaking()->InviteUserToLobby(...);
	// 					SteamFriends()->InviteUserToGame(...);
	// 					textInput.reset();
	// 				}
	// 			);
	// 		}
	// 		else
	// 			textInput.reset();
	// 	}
	// ));

    return true;
}

bool LobbyView::Release()
{
    lobby.reset();
	game->LeaveLobby();

	return true;
}

void LobbyView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textInput)
		textInput->OnMouseDown(x, y);
}

void LobbyView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void LobbyView::OnKeyDown(SDL_Keysym key)
{
	if (textInput)
		textInput->OnKeyDown(key);
}

void LobbyView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

void LobbyView::OnTextInput(SDL_TextInputEvent inputEvent)
{
	if (textInput)
		textInput->OnTextInput(inputEvent);
}

void LobbyView::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
	if (textInput)
		textInput->OnTextEditing(editingEvent);
}

bool LobbyView::Update()
{
	return true;
}

bool LobbyView::Display(const SDLRendererPtr& renderEngine)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->Display(renderEngine);
	}

	if (textInput)
		textInput->Display(renderEngine);

	if (textOutputDisplay)
		textOutputDisplay->Display(renderEngine);

	int offsetY = 350;
	std::string lobbyMembersString{"Lobby members:\n"};
	for (const auto& player : lobby->GetLobbyMembers())
	{
		const char* lobbyMemberNickname = nullptr;

		lobbyMemberNickname = SteamFriends()->GetFriendPersonaName(player);

		lobbyMembersString += lobbyMemberNickname;
		lobbyMembersString += "\n";
		offsetY += 50;
	}

	textOutputDisplay->SetDisplayText(lobbyMembersString);

	return true;
}