#ifndef SDL_RENDERER_H
#define SDL_RENDERER_H

#include "SDLWindow.h"

#include <vector>

enum class TextAlign
{
	TEXTALIGN_DEFAULT,
	TEXTALIGN_CENTER
};

class SDLRenderer
{
public:

    SDLRenderer(const SDLWindowPtr& window);
    
    bool Init();
    void Release();
    
    bool StartScene(int backgroundImageIndex);
	bool EndScene();
    SDL_Renderer* GetHandle() const;

    bool DisplayText(const std::string& text, TextAlign textAlign, bool wrap, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const SDL_Color& color);
    bool DisplayTextScroll(const std::string& text, TextAlign textAlign, bool wrap, uint32_t& scrollOffset, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const SDL_Color& color);

private:

    TTF_Font* font;
    std::vector<SDL_Texture*> backgroundImages;

    SDL_Renderer* handle;
    SDLWindowPtr window;
};

using SDLRendererPtr = std::shared_ptr<SDLRenderer>;

#endif