#include "AchievementsView.h"
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
inline std::shared_ptr<TextInput> MakeTextInput(std::string label, int offsetY, GUIAction action)
{
    return std::make_shared<TextInput>(std::move(label), 1280 / 2 - 150, offsetY, 300, BUTTON_HEIGHT, std::move(action));
}

AchievementsView::AchievementsView(const GamePtr& _game, const StatsAndAchievementsPtr& _statsAndAchievements)
    : GameState(_game)
	, statsAndAchievements(_statsAndAchievements)
{
}

bool AchievementsView::Init()
{
	std::string achievementsInitString{"To display achievements click \"GET ACHIEVEMENTS\".\nAfter every update click the button again.\n"};
	textOutputDisplay = MakeTextOutputDisplay("ACHIEVEMENTS VIEW TEXT OUTPUT", 400, 150, 800, 400,
		[&]()
		{
			printf("Achievements View Text Output\n");textOutputDisplay->SetDisplayText(achievementsInitString);
		});
	textOutputDisplay->SetDisplayText(achievementsInitString);

	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY,
		[&]()
		{
			printf("Main Menu\n");game->SetGameState(GameState::State::START_MENU);
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("ACHIEVEMENT TEST 0 SET", offsetX, offsetY,
		[&]()
		{
			printf("ACH_TEST_0 set\n");statsAndAchievements->SetAchievement("ACH_TEST_0");
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("ACHIEVEMENT TEST 0 CLEAR", offsetX, offsetY,
		[&]()
		{
			printf("ACH_TEST_0 clear\n");statsAndAchievements->ClearAchievement("ACH_TEST_0");
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("GET ACHIEVEMENTS", offsetX, offsetY,
		[&]() 
		{
			printf("GetAchievements\n");
			statsAndAchievements->RequestStats();
			Achievement_t *pAchievements = statsAndAchievements->GetAchievementsData();
			std::string achievementsString = "Achievement: %s; Description: %s; Achieved: %d\n";
			std::string achStrResult;
			for (int iAch=0; iAch<statsAndAchievements->GetNumAchievements(); ++iAch)
			{
				int size_s = std::snprintf(nullptr, 0, achievementsString.c_str(), pAchievements[iAch].m_rgchName, pAchievements[iAch].m_rgchDescription, pAchievements[iAch].m_bAchieved);
				auto size = static_cast<size_t>(size_s);
				std::unique_ptr<char[]> buf(new char[size]);
				std::snprintf(buf.get(), size, achievementsString.c_str(), pAchievements[iAch].m_rgchName, pAchievements[iAch].m_rgchDescription, pAchievements[iAch].m_bAchieved);
				std::string str(buf.get());
				achStrResult += str;
				achStrResult += "\n";
			}
			textOutputDisplay->SetDisplayText(achStrResult);
			SDL_Log(achStrResult.c_str());
		}));

	textLink = MakeLink("CLICK THIS LINK AND LEAVE YOUR FEEDBACK PLEASE", 0, 670, 1280, 50, "https://forms.gle/3h2oULcDGaDsZKMdA");

    return true;
}

bool AchievementsView::Release()
{
	return true;
}

void AchievementsView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textLink)
		textLink->OnMouseDown(x, y);
}

void AchievementsView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void AchievementsView::OnKeyDown(SDL_Keysym key)
{
}

void AchievementsView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

void AchievementsView::OnTextInput(SDL_TextInputEvent inputEvent)
{
}

void AchievementsView::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
}

bool AchievementsView::Update()
{
	return true;
}

bool AchievementsView::Display(const SDLRendererPtr& renderEngine)
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