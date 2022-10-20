#ifndef LEADERBOARDS_VIEW_H
#define LEADERBOARDS_VIEW_H

#include "GameState.h"
#include <game/gui/Button.h>
#include <game/gui/TextOutputDisplay.h>
#include <game/gui/TextLink.h>
#include <game/gui/TextInput.h>
#include <game/steam/Leaderboards.h>

#include <vector>
#include <string>

class LeaderboardsView : public GameState
{
public:

    LeaderboardsView(const GamePtr& _game, const LeaderboardsPtr& _leaderboards);

    virtual bool Init() override;
    virtual bool Release() override;

    virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) override;
    virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) override;
    virtual void OnKeyDown(SDL_Keysym key) override;
    virtual void OnMouseWheel(SDL_MouseWheelEvent mouseWheel) override;
    virtual void OnTextInput(SDL_TextInputEvent inputEvent) override;
	virtual void OnTextEditing(SDL_TextEditingEvent editingEvent) override;

    virtual bool Update() override;
    virtual bool Display(const SDLRendererPtr& renderEngine) override;

private:

    LeaderboardsPtr leaderboards;
    std::vector<ButtonPtr> buttons;
    TextOutputDisplayPtr textOutputDisplay;
    TextLinkPtr textLink;
    TextInputPtr textInput;
};

#endif