#include "Button.h"

#include <SDL2_gfxPrimitives.h>

Button::Button(const std::string& _caption, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, const GUIAction& _action)
        : caption{_caption}
        , x{_x}
        , y{_y}
        , width{_width}
        , height{_height}
        , action{_action}
        , isHovered{false}
{
}

bool Button::IsPointInside(std::uint32_t _x, std::uint32_t _y)
{
    return _x > x && _x < x + width
        && _y > y && _y < y + height;
}

void Button::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        return;

    action();
}

void Button::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        isHovered = false;
    else
        isHovered = true;
}

bool Button::DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color)
{
    return roundedBoxRGBA(renderer, rect.x, rect.y, rect.w, rect.h, radius, color.r, color.g, color.b, color.a) == 0;
}

bool Button::Display(const SDLRendererPtr& renderer)
{
    const SDL_Rect rect{x, y, x+width, y+height};
    SDL_Color color{0, 0, 0, 255};
    if(!isHovered)
        color = {236, 236, 236, 255};
    else
        color = {108, 122, 137, 255};

    DrawRoundedBox(renderer->GetHandle(), rect, 10, color);

    renderer->DisplayText(caption, TextAlign::TEXTALIGN_CENTER, false, x, y, width, height, {0, 0, 0, 255});
    
    return true;
}
