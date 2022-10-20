#include "StatsView.h"
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

StatsView::StatsView(const GamePtr& _game, const StatsAndAchievementsPtr& _statsAndAchievements)
    : GameState(_game)
	, statsAndAchievements(_statsAndAchievements)
{
}

bool StatsView::Init()
{
	std::string statsInitString{"To display stats first click \"GET STATS\".\nAfter every update click the button again.\n"};
	textOutputDisplay = MakeTextOutputDisplay("STATS VIEW TEXT OUTPUT", 400, 150, 800, 400,
		[&]() {printf("Stats View Text Output\n");textOutputDisplay->SetDisplayText(statsInitString);});
	textOutputDisplay->SetDisplayText(statsInitString);

	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY,
		[&]()
		{
			printf("Main Menu\n");game->SetGameState(GameState::State::START_MENU);
		}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("INC INT STAT BY 1", offsetX, offsetY,
		[&]() 
		{
			printf("STAT_TEST_0++\n");
			int statValue = statsAndAchievements->GetStatsData()[STAT_TEST_0].m_iValue;
			statsAndAchievements->SetStat(STAT_TEST_0, statValue + 1);
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("INC FLOAT1 STAT BY 1.37", offsetX, offsetY,
		[&]()
		{
			printf("STAT_TEST_1++\n");
			float statValue = statsAndAchievements->GetStatsData()[STAT_TEST_1].m_flValue;
			statsAndAchievements->SetStat(STAT_TEST_1, statValue + 1.37f);
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("INC FLOAT2 STAT BY 3.14", offsetX, offsetY,
		[&]()
		{
			printf("STAT_TEST_2++\n");
			float statValue = statsAndAchievements->GetStatsData()[STAT_TEST_2].m_flValue;
			statsAndAchievements->SetStat(STAT_TEST_2, statValue + 3.14f);
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("AVG STAT_TEST_1/0.225", offsetX, offsetY,
		[&]()
		{
			float statFloat1Value = statsAndAchievements->GetStatsData()[STAT_TEST_1].m_flValue;
			float statFloat2Value = statsAndAchievements->GetStatsData()[STAT_TEST_2].m_flValue;
			printf("STAT_TEST_3 get AVG of STAT_TEST_1 and 0.225\n");
			statsAndAchievements->SetAvgRateStat(STAT_TEST_3, statFloat1Value, 0.225f);
		}));
	offsetY += PADDING;
    buttons.emplace_back(MakeButton("GET STATS", offsetX, offsetY,
		[&]() 
		{
			SDL_Log("Get Stats\n");
			statsAndAchievements->RequestStats();
			Stat_t *pStats = statsAndAchievements->GetStatsData();
			std::string statsString;
			std::string statsStrResult;
			for (int iStat=0; iStat<statsAndAchievements->GetNumStats(); ++iStat)
			{
				Stat_t &stat = pStats[iStat];
				int size_s;
				switch (stat.m_eStatType)
				{
				case STAT_INT:
					statsString = "Stat: %s Value: %d\n";
					size_s = std::snprintf(nullptr, 0, statsString.c_str(), stat.m_pchStatName, stat.m_iValue);
					break;

				case STAT_FLOAT:
					statsString = "Stat: %s Value: %f\n";
					size_s = std::snprintf(nullptr, 0, statsString.c_str(), stat.m_pchStatName, stat.m_flValue);
					break;

				case STAT_AVGRATE:
					statsString = "AvgStat: %s Value: %f\n";
					size_s = std::snprintf(nullptr, 0, statsString.c_str(), stat.m_pchStatName, stat.m_flValue);
					break;

				default:
					break;
				};
				auto size = static_cast<size_t>(size_s);
				std::unique_ptr<char[]> buf(new char[size]);
				if (stat.m_eStatType == STAT_INT)
				{
					std::snprintf(buf.get(), size, statsString.c_str(), stat.m_pchStatName, stat.m_iValue);
				}
				else
				{
					std::snprintf(buf.get(), size, statsString.c_str(), stat.m_pchStatName, stat.m_flValue);
				}
				std::string str(buf.get());
				statsStrResult += str;
				statsStrResult += "\n";
			}
			textOutputDisplay->SetDisplayText(statsStrResult);
			SDL_Log(statsStrResult.c_str());
		}));

	textLink = MakeLink("CLICK THIS LINK AND LEAVE YOUR FEEDBACK PLEASE", 0, 670, 1280, 50, "https://forms.gle/3h2oULcDGaDsZKMdA");

	return true;
}

bool StatsView::Release()
{
	return true;
}

void StatsView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textLink)
		textLink->OnMouseDown(x, y);
}

void StatsView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void StatsView::OnKeyDown(SDL_Keysym key)
{
}

void StatsView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

void StatsView::OnTextInput(SDL_TextInputEvent inputEvent)
{
}

void StatsView::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
}

bool StatsView::Update()
{
	return true;
}

bool StatsView::Display(const SDLRendererPtr& renderEngine)
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