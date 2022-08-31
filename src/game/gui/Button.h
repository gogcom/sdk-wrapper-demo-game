#ifndef BUTTON_H
#define BUTTON_H

#include <engine/SDLRenderer.h>
#include <string>
#include <functional>

using GUIAction = std::function<void()>;

class Button
{
public:

    Button(
        const std::string& caption,
        uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const GUIAction& _action);

    void OnMouseDown(std::uint32_t x, std::uint32_t y);
    void OnMouseMotion(std::uint32_t x, std::uint32_t y);
    bool Display(const SDLRendererPtr& renderer);
    bool IsPointInside(std::uint32_t x, std::uint32_t y);
    bool DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color);

private:

    GUIAction action;
    bool isHovered;
    const std::string caption;
    const uint32_t x, y, width, height;
};

using ButtonPtr = std::shared_ptr<Button>;

#endif