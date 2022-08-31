#include "StartMenu.h"
#include <game/SWDemo.h>

constexpr auto BUTTON_HEIGHT = 50;
constexpr auto PADDING = BUTTON_HEIGHT + 15;

inline std::shared_ptr<Button> MakeButton(std::string label, int offsetX, int offsetY, GUIAction action)
{
    return std::make_shared<Button>(std::move(label), offsetX, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

inline std::shared_ptr<TextLink> MakeLink(std::string label, int x, int y, int w, int h, std::string link)
{
    return std::make_shared<TextLink>(std::move(label), x, y, w, h, std::move(link));
}

StartMenu::StartMenu(const GamePtr& _game)
    : GameState(_game)
{
}

bool StartMenu::Init()
{
	int offsetX = 25;
	int offsetY = 150;
    buttons.emplace_back(MakeButton("ACHIEVEMENTS", offsetX, offsetY, [&]() {printf("Achievements\n");game->SetGameState(GameState::State::ACHIEVEMENTS_VIEW);}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("STATS", offsetX, offsetY, [&]() {printf("Stats\n");game->SetGameState(GameState::State::STATS_VIEW);}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("LEADERBOARDS", offsetX, offsetY, [&]() {printf("Leaderboards\n");game->SetGameState(GameState::State::LEADERBOARDS_VIEW);}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("FRIENDS", offsetX, offsetY, [&]() {printf("Friends\n");game->SetGameState(GameState::State::FRIENDS_VIEW);}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("QUIT", offsetX, offsetY, [&]() {printf("Quit\n");game->Close();}));

	textLink = MakeLink("CLICK THIS LINK AND LEAVE YOUR FEEDBACK PLEASE", 0, 670, 1280, 50, "https://forms.gle/3h2oULcDGaDsZKMdA");
    return true;
}

bool StartMenu::Release()
{
	return true;
}

void StartMenu::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textLink)
		textLink->OnMouseDown(x, y);
}

void StartMenu::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void StartMenu::OnKeyDown(SDL_Keysym key)
{
}

void StartMenu::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

bool StartMenu::Update()
{
	return true;
}

bool StartMenu::Display(const SDLRendererPtr& renderEngine)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->Display(renderEngine);
	}

	if (textLink)
		textLink->Display(renderEngine);

	return true;
}