#ifndef LOBBY_VIEW_H
#define LOBBY_VIEW_H

#include "GameState.h"
#include <game/gui/Button.h>
#include <game/gui/TextInput.h>
#include <game/gui/TextOutputDisplay.h>
#include <game/steam/Lobby.h>

#include <vector>
#include <string>

class LobbyView : public GameState
{
public:

    LobbyView(const GamePtr& _game, const LobbyPtr& _lobby);

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

    LobbyPtr lobby;
    std::vector<ButtonPtr> buttons;
    TextInputPtr textInput;
    TextOutputDisplayPtr textOutputDisplay;
};

#endif