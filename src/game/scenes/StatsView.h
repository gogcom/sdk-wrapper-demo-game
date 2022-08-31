#ifndef STATS_VIEW_H
#define STATS_VIEW_H

#include "GameState.h"
#include <game/gui/Button.h>
#include <game/gui/TextOutputDisplay.h>
#include <game/gui/TextLink.h>
#include <game/steam/StatsAndAchievements.h>

#include <vector>
#include <string>

class StatsView : public GameState
{
public:

    StatsView(const GamePtr& _game, const StatsAndAchievementsPtr& _statsAndAchievements);

    virtual bool Init() override;
    virtual bool Release() override;

    virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) override;
    virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) override;
    virtual void OnKeyDown(SDL_Keysym key) override;
    virtual void OnMouseWheel(SDL_MouseWheelEvent mouseWheel) override;

    virtual bool Update() override;
    virtual bool Display(const SDLRendererPtr& renderEngine) override;

private:

    StatsAndAchievementsPtr statsAndAchievements;
    std::vector<ButtonPtr> buttons;
    TextOutputDisplayPtr textOutputDisplay;
    TextLinkPtr textLink;
};

#endif