#ifndef TEXT_OUTPUT_DISPLAY_H
#define TEXT_OUTPUT_DISPLAY_H

#include <engine/SDLRenderer.h>
#include <string>
#include <functional>

using GUIAction = std::function<void()>;

class TextOutputDisplay
{
public:

    TextOutputDisplay(
        const std::string& caption,
        uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const GUIAction& _action);

    void OnMouseDown(std::uint32_t x, std::uint32_t y);
    void OnMouseMotion(std::uint32_t x, std::uint32_t y);
    void OnMouseWheel(SDL_MouseWheelEvent mouseWheel);
    bool Display(const SDLRendererPtr& renderer);
    bool IsPointInside(std::uint32_t x, std::uint32_t y);
    bool DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color);
    bool DrawBox(SDL_Renderer* renderer, SDL_Rect rect, SDL_Color color);

    void SetDisplayText(std::string& displayText)
    {
        text = displayText;
    }
    std::string GetDisplayText()
    {
        return text;
    }

private:

    GUIAction action;
    bool isHovered;
    const std::string caption;
    std::string text;
    const uint32_t x, y, width, height;
    uint32_t scrollOffset;
};

using TextOutputDisplayPtr = std::shared_ptr<TextOutputDisplay>;

#endif