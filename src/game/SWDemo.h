#ifndef SW_DEMO_H
#define SW_DEMO_H

#pragma once
#include <steam_api.h>
#include <vector>

#include <game/scenes/GameState.h>
#include <engine/SDLRenderer.h>

static bool stateChanged = false;

class CStatsAndAchievements;
using StatsAndAchievementsPtr = std::shared_ptr<CStatsAndAchievements>;

class CLeaderboards;
using LeaderboardsPtr = std::shared_ptr<CLeaderboards>;

class CFriends;
using FriendsPtr = std::shared_ptr<CFriends>;

namespace galaxy
{
	namespace api
	{
		extern bool IsFullyInitialized;
	}
}

class SWDemo : public std::enable_shared_from_this<SWDemo>
{
    public:

        SWDemo(const SDLRendererPtr& renderer);

        bool Init(int argc, char** argv);
        void Close();
        bool Release();
        bool IsRunning() const;
        bool Update();

        void OnMouseDown(std::uint32_t x, std::uint32_t y);
        void OnMouseMotion(std::uint32_t x, std::uint32_t y);
        void OnKeyDown(SDL_Keysym key);
        void OnMouseWheel(SDL_MouseWheelEvent mouseWheel);

        bool SetGameState(const GameState::State& gameState);

        bool IsUserLoggedIn()
        {
            return isLoggedIn;
        }

        std::string GetUserName()
        {
            return userName;
        }

    private:

        bool closeRequested;

        bool isLoggedIn;
        std::string userName;

        GameStatePtr gameState;
		GameState::State currentGameState;
        SDLRendererPtr renderer;

        StatsAndAchievementsPtr statsAndAchievements;
        LeaderboardsPtr leaderboards;
        FriendsPtr friends;
};

using GamePtr = std::shared_ptr<SWDemo>;

#endif