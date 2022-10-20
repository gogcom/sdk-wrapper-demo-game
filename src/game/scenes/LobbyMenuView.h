#ifndef LOBBY_MENU_VIEW_H
#define LOBBY_MENU_VIEW_H

#include "GameState.h"
#include <game/gui/Button.h>
#include <game/gui/TextInput.h>

#include <vector>
#include <string>

class LobbyMenuView : public GameState
{
public:

    LobbyMenuView(const GamePtr& _game);

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

    std::vector<ButtonPtr> buttons;
    TextInputPtr textInput;
};

#endif