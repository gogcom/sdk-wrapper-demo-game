#ifndef START_MENU_H
#define START_MENU_H

#include "GameState.h"
#include <game/gui/Button.h>
#include <game/gui/TextLink.h>
#include <vector>
#include <string>

class StartMenu : public GameState
{
public:

    StartMenu(const GamePtr& _game);

    virtual bool Init() override;
    virtual bool Release() override;

    virtual void OnMouseDown(std::uint32_t x, std::uint32_t y) override;
    virtual void OnMouseMotion(std::uint32_t x, std::uint32_t y) override;
    virtual void OnKeyDown(SDL_Keysym key) override;
    virtual void OnMouseWheel(SDL_MouseWheelEvent mouseWheel) override;

    virtual bool Update() override;
    virtual bool Display(const SDLRendererPtr& renderEngine) override;

private:

    std::vector<ButtonPtr> buttons;
    TextLinkPtr textLink;
    std::string dlcStatus{"DLC not installed."};
};

#endif