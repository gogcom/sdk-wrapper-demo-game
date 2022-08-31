#include "TextLink.h"

#if defined(_WIN32)
#include <windows.h>
#include <shellapi.h>
#endif

TextLink::TextLink(const std::string& _caption, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, const std::string& _linkText)
        : caption{_caption}
        , x{_x}
        , y{_y}
        , width{_width}
        , height{_height}
        , linkText{_linkText}
        , isHovered{false}
        , wasClicked{false}
{
}

bool TextLink::IsPointInside(std::uint32_t _x, std::uint32_t _y)
{
    return _x > x && _x < x + width
        && _y > y && _y < y + height;
}

void TextLink::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        return;

    if (!wasClicked)
        wasClicked = true;

    ShellExecuteA(NULL, NULL, linkText.c_str(), NULL, NULL, SW_SHOWNORMAL);
}

void TextLink::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        isHovered = false;
    else
        isHovered = true;
}

bool TextLink::Display(const SDLRendererPtr& renderer)
{
    SDL_Color color{0,0,0,255};

    if (wasClicked)
        color = {177, 49, 228, 255};
    else
        color = {236, 234, 66, 255};

    renderer->DisplayText(caption, TextAlign::TEXTALIGN_CENTER, false, x, y, width, height, color);
    
    return true;
}
