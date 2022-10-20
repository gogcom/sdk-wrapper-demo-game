#include "FriendsView.h"
#include <game/SWDemo.h>

constexpr auto BUTTON_HEIGHT = 50;
constexpr auto PADDING = BUTTON_HEIGHT + 15;

inline std::shared_ptr<Button> MakeButton(std::string label, int offsetX, int offsetY, GUIAction action)
{
    return std::make_shared<Button>(std::move(label), offsetX, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}
inline std::shared_ptr<TextOutputDisplay> MakeTextOutputDisplay(std::string label, int x, int y, int w, int h, GUIAction action)
{
    return std::make_shared<TextOutputDisplay>(std::move(label), x, y, w, h, std::move(action));
}
inline std::shared_ptr<TextLink> MakeLink(std::string label, int x, int y, int w, int h, std::string link)
{
    return std::make_shared<TextLink>(std::move(label), x, y, w, h, std::move(link));
}

FriendsView::FriendsView(const GamePtr& _game, const FriendsPtr& _friends)
    : GameState(_game)
	, friends(_friends)
{
}

bool FriendsView::Init()
{
	std::string friendsInitString{"To display friends first click \"REQUEST GLX FRIEND COUNT\".\nThen click the \"SHOW FRIENDS\" button.\n"};
	textOutputDisplay = MakeTextOutputDisplay("FRIENDS VIEW TEXT OUTPUT", 400, 150, 800, 400,
		[&]()
		{
			printf("Friends View Text Output\n");textOutputDisplay->SetDisplayText(friendsInitString);
		});
	textOutputDisplay->SetDisplayText(friendsInitString);

	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY,
		[&]()
		{
			printf("Main Menu\n");game->SetGameState(GameState::State::START_MENU);
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("REQUEST GLX FRIEND COUNT", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Request GLX friend count\n");
			friends->RequestGalaxyFriends();
			std::string friendsCountString{"Friends count: "};
			friendsCountString += std::to_string(friends->GetFriendCount());
			textOutputDisplay->SetDisplayText(friendsCountString);

		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("SHOW ALL FRIENDS", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Show All Friends\n");
			// only k_EFriendFlagImmediate is relevant, rest is ignored
			const int friendFlags = k_EFriendFlagImmediate | k_EFriendFlagOnGameServer | k_EFriendFlagRequestingInfo;
			int friendCount = friends->GetFriendCount();
			std::string friendsPersonas = "All Friends:\n";
			for (int i = 0; i < friendCount; i++)
			{
				CSteamID steamFriend = SteamFriends()->GetFriendByIndex(i, friendFlags);
				friendsPersonas += friends->GetFriendPersonaName(steamFriend);
				friendsPersonas += "\n";

			}
			textOutputDisplay->SetDisplayText(friendsPersonas);
			SDL_Log(friendsPersonas.c_str());
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("SHOW ONLINE FRIENDS", offsetX, offsetY,
		[&]()
		{
			SDL_Log("Show Online Friends\n");
			// only k_EFriendFlagImmediate is relevant, rest is ignored
			const int friendFlags = k_EFriendFlagImmediate | k_EFriendFlagOnGameServer | k_EFriendFlagRequestingInfo;
			int friendCount = friends->GetFriendCount();
			std::string friendsPersonas = "Online Friends:\n";
			for (int i = 0; i < friendCount; i++)
			{
				CSteamID steamFriend = SteamFriends()->GetFriendByIndex(i, friendFlags);
				if(SteamFriends()->GetFriendPersonaState(steamFriend) == EPersonaState::k_EPersonaStateOnline)
				{
					friendsPersonas += friends->GetFriendPersonaName(steamFriend);
					friendsPersonas += "\n";
				}
			}
			textOutputDisplay->SetDisplayText(friendsPersonas);
			SDL_Log(friendsPersonas.c_str());
		}));

	textLink = MakeLink("CLICK THIS LINK AND LEAVE YOUR FEEDBACK PLEASE", 0, 670, 1280, 50, "https://forms.gle/3h2oULcDGaDsZKMdA");

    return true;
}

bool FriendsView::Release()
{
	return true;
}

void FriendsView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textLink)
		textLink->OnMouseDown(x, y);
}

void FriendsView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}

	if (textOutputDisplay)
		textOutputDisplay->OnMouseMotion(x, y);
}

void FriendsView::OnKeyDown(SDL_Keysym key)
{
}

void FriendsView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
	if (textOutputDisplay)
		textOutputDisplay->OnMouseWheel(mouseWheel);
}

void FriendsView::OnTextInput(SDL_TextInputEvent inputEvent)
{
}

void FriendsView::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
}

bool FriendsView::Update()
{
	return true;
}

bool FriendsView::Display(const SDLRendererPtr& renderEngine)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->Display(renderEngine);
	}

	if (textOutputDisplay)
		textOutputDisplay->Display(renderEngine);

	if (textLink)
		textLink->Display(renderEngine);

	return true;
}