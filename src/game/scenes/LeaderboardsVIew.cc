#include "LeaderboardsView.h"
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

LeaderboardsView::LeaderboardsView(const GamePtr& _game, const LeaderboardsPtr& _leaderboards)
    : GameState(_game)
	, leaderboards(_leaderboards)
{
}

bool LeaderboardsView::Init()
{
	std::string leaderboardsInitString{"To display achievements first click \"FIND LEADERBOARD\".\nIf leaderboard was found click the \"DOWNLOAD SCORE\" button.\nAfter every update click the button again.\n"};
	textOutputDisplay = MakeTextOutputDisplay("LEADERBOARDS VIEW TEXT OUTPUT", 400, 150, 800, 400, [&]() {printf("Leaderboards View Text Output\n");textOutputDisplay->SetDisplayText(leaderboardsInitString);});
	textOutputDisplay->SetDisplayText(leaderboardsInitString);

	int offsetX = 25;
	int offsetY = 150;
	buttons.emplace_back(MakeButton("MAIN MENU", offsetX, offsetY, [&]() {printf("Main Menu\n");game->SetGameState(GameState::State::START_MENU);}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("FIND LEADERBOARD", offsetX, offsetY, [&]() 
	{
		SDL_Log("Find Leaderboard\n");
		leaderboards->FindLeaderboard("TEST_LEADERBOARD");
		std::string leaderboardsCountString{"Found Leaderboard: "};
		leaderboardsCountString += std::to_string(leaderboards->GetCurrentLeaderboard());
		textOutputDisplay->SetDisplayText(leaderboardsCountString);
	}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("DOWNLOAD SCORE", offsetX, offsetY, [&]() {printf("Download Score\n");leaderboards->DownloadScores();}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("INCREASE TOP SCORE  BY 200", offsetX, offsetY, [&]()
	{
		SDL_Log("Increase top score by 200\n");
		leaderboards->UploadScore(leaderboards->GetLeaderboardEntry(0)->m_nScore+200);
		std::string increseTopScoreString{"Increased top score by 200\nDownload scores again"};
		textOutputDisplay->SetDisplayText(increseTopScoreString);
	}));
	offsetY += PADDING;
	buttons.emplace_back(MakeButton("SHOW SCORES", offsetX, offsetY, [&]() {
		printf("Show Scores\n");
		std::string leaderboardString = "Entry: %d Score: %d\n";
		std::string ldbStrResult;
		for (int i = 0; i < leaderboards->GetLeaderboardEntriesCount(); i++)
		{
			LeaderboardEntry_t* entry = leaderboards->GetLeaderboardEntry(i);
			int size_s = std::snprintf(nullptr, 0, leaderboardString.c_str(), entry->m_nGlobalRank, entry->m_nScore);
			auto size = static_cast<size_t>(size_s);
			std::unique_ptr<char[]> buf(new char[size]);
			std::snprintf(buf.get(), size, leaderboardString.c_str(), entry->m_nGlobalRank, entry->m_nScore);
			std::string str(buf.get());
			ldbStrResult += str;
			ldbStrResult += "\n";
		}
		textOutputDisplay->SetDisplayText(ldbStrResult);
        SDL_Log(ldbStrResult.c_str());
	}));

	textLink = MakeLink("CLICK THIS LINK AND LEAVE YOUR FEEDBACK PLEASE", 0, 670, 1280, 50, "https://forms.gle/3h2oULcDGaDsZKMdA");

    return true;
}

bool LeaderboardsView::Release()
{
	return true;
}

void LeaderboardsView::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseDown(x, y);
	}

	if (textLink)
		textLink->OnMouseDown(x, y);
}

void LeaderboardsView::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
	for (const auto& button : buttons)
	{
		if (button)
			button->OnMouseMotion(x, y);
	}
}

void LeaderboardsView::OnKeyDown(SDL_Keysym key)
{
}

void LeaderboardsView::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{
}

bool LeaderboardsView::Update()
{
	return true;
}

bool LeaderboardsView::Display(const SDLRendererPtr& renderEngine)
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