#ifndef GAME_STATE_H
#define GAME_STATE_H

#include <engine/SDLRenderer.h>

#include <utility>
#include <random>



class SWDemo;
using GamePtr = std::shared_ptr<SWDemo>;

class GameState
{
public:

	enum class State
	{
		START_MENU,
		ACHIEVEMENTS_VIEW,
		STATS_VIEW,
		LEADERBOARDS_VIEW,
		FRIENDS_VIEW
	};

	explicit GameState(GamePtr _game)
		: game(std::move(_game))
	{
		ChooseRandomBackground();
	}

	virtual ~GameState() = default;

	virtual bool Init() = 0;
	virtual bool Release() = 0;

	virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) = 0;
	virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) = 0;
	virtual void OnKeyDown(SDL_Keysym key) = 0;
	virtual void OnMouseWheel(SDL_MouseWheelEvent mouseWheel) = 0;

	virtual bool Update() = 0;

	virtual void ChooseRandomBackground() final
	{
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_int_distribution<> distr(0, 4);
		backgroundImageIndex =  distr(gen);
	}

	virtual bool Render(const SDLRendererPtr& renderEngine, std::string username, bool isLoggedIn) final
	{
		renderEngine->StartScene(backgroundImageIndex);

		auto ret = Display(renderEngine);

		if(isLoggedIn)
		{
			renderEngine->DisplayText(username, TextAlign::TEXTALIGN_DEFAULT, false, 120, 20, 100, 50, {255, 255, 255, 255});
		}
		else
		{
			renderEngine->DisplayText("Not logged in", TextAlign::TEXTALIGN_DEFAULT, false, 120, 20, 100, 50, {255, 255, 255, 255});
		}

		renderEngine->EndScene();

		return ret;
	}

protected:

	virtual bool Display(const SDLRendererPtr& renderEngine) = 0;

	int backgroundImageIndex{0};
	GamePtr game;
};

using GameStatePtr = std::shared_ptr<GameState>;

#endif