#include "LobbyMenuView.h"
#include <game/SWDemo.h>

constexpr auto BUTTON_HEIGHT = 50;
constexpr auto PADDING = BUTTON_HEIGHT + 15;

inline std::shared_ptr<Button> MakeButton(std::string label, int offsetX, int offsetY, GUIAction action)
{
    return std::make_shared<Button>(std::move(label), offsetX, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

inline std::shared_ptr<TextInput> MakeTextInput(std::string label, int offsetY, GUIAction action)
{
    return std::make_shared<TextInput>(std::move(label), 1280 / 2 - 150, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

LobbyMenuView::LobbyMenuView(const GamePtr& _game)
    : GameState(_game)
{
}

bool LobbyMenuView::Init()
{
	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Main Menu\n");game->SetGameState(GameState::State::START_MENU);
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("CREATE LOBBY", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Create lobby\n");
			game->CreateLobby();
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("JOIN LOBBY", offsetX, offsetY,
		[&, offset = offsetY]()
		{
			SDL_Log("Join lobby\n");
			textInput = MakeTextInput("Enter connection string", offset + PADDING,
				[&]()
				{
					
				});
		}));
	offsetY += PADDING;

    return true;
}

bool LobbyMenuView::Release()
{
	return true;
}

void LobbyMenuView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textInput)
		textInput->OnMouseDown(x, y);
}

void LobbyMenuView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void LobbyMenuView::OnKeyDown(SDL_Keysym key)
{
	if (textInput)
		textInput->OnKeyDown(key);
}

void LobbyMenuView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

void LobbyMenuView::OnTextInput(SDL_TextInputEvent inputEvent)
{
	// if (textInput)
	// 	textInput->OnTextInput(inputEvent);
}

void LobbyMenuView::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
	// if (textInput)
	// 	textInput->OnTextEditing(editingEvent);
}

bool LobbyMenuView::Update()
{
	return true;
}

bool LobbyMenuView::Display(const SDLRendererPtr& renderEngine)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->Display(renderEngine);
	}

	if (textInput)
		textInput->Display(renderEngine);

	return true;
}