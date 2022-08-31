#include "TextOutputDisplay.h"

#include <SDL2_gfxPrimitives.h>

TextOutputDisplay::TextOutputDisplay(const std::string& _caption, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, const GUIAction& _action)
        : caption{_caption}
        , x{_x}
        , y{_y}
        , width{_width}
        , height{_height}
        , action{_action}
        , isHovered{false}
        , scrollOffset{0}
{
}

bool TextOutputDisplay::IsPointInside(std::uint32_t _x, std::uint32_t _y)
{
    return _x > x && _x < x + width
        && _y > y && _y < y + height;
}

void TextOutputDisplay::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        return;

    action();
}

void TextOutputDisplay::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        isHovered = false;
    else
        isHovered = true;
}

void TextOutputDisplay::OnMouseWheel(SDL_MouseWheelEvent mouseWheel)
{    
    if (isHovered)
    {
        SDL_Log("Friends MouseWheelEvent; mouseWheel.y: %d", mouseWheel.y);
        if(mouseWheel.y > 0) // scroll up
        {
            if (scrollOffset == 0 || mouseWheel.y > scrollOffset)
                scrollOffset = 0;
            else
                scrollOffset -= mouseWheel.y;
        }
        else if(mouseWheel.y < 0) // scroll down
        {
                scrollOffset += -mouseWheel.y;
        }
        SDL_Log("TextOutputDisplay scrollOffset: %d", scrollOffset);
    }
}

bool TextOutputDisplay::DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color)
{
    return roundedBoxRGBA(renderer, rect.x, rect.y, rect.w, rect.h, radius, color.r, color.g, color.b, color.a) == 0;
}

bool TextOutputDisplay::DrawBox(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color)
{
    return boxRGBA(renderer, rect.x, rect.y, rect.w, rect.h, color.r, color.g, color.b, color.a) == 0;
}

bool TextOutputDisplay::Display(const SDLRendererPtr& renderer)
{
    const SDL_Rect rect{x, y, x+width, y+height};
    SDL_Color color{0, 0, 0, 100};

    DrawRoundedBox(renderer->GetHandle(), rect, 5, color);

    renderer->DisplayTextScroll(text, TextAlign::TEXTALIGN_DEFAULT, true, scrollOffset, x, y, width, height, {255, 255, 255, 255});
    
    return true;
}
