#ifndef TEXT_LINK_H
#define TEXT_LINK_H

#include <engine/SDLRenderer.h>
#include <string>

class TextLink
{
public:

    TextLink(
        const std::string& caption,
        uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const std::string& linkText);

    void OnMouseDown(std::uint32_t x, std::uint32_t y);
    void OnMouseMotion(std::uint32_t x, std::uint32_t y);
    bool Display(const SDLRendererPtr& renderer);
    bool IsPointInside(std::uint32_t x, std::uint32_t y);

private:

    bool isHovered;
    bool wasClicked;
    const std::string caption;
    const std::string linkText;
    const uint32_t x, y, width, height;
};

using TextLinkPtr = std::shared_ptr<TextLink>;

#endif