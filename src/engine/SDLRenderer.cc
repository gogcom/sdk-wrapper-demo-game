#include "SDLRenderer.h"

#include <SDL_image.h>

SDLRenderer::SDLRenderer(const SDLWindowPtr& window)
    : window(window)
{
}

bool SDLRenderer::Init()
{
    handle = SDL_CreateRenderer(window->GetHandle(), -1, SDL_RENDERER_ACCELERATED);
    
    if(!handle)
        return false;

    for (int i = 1; i <= 5; i++)
    {
        std::string texture = "images/Meet_00" + std::to_string(i) + ".jpg";
        SDL_Surface* surface = IMG_Load(texture.c_str());
        if (!surface)
            return false;
        backgroundImages.push_back(SDL_CreateTextureFromSurface(handle, surface));
        SDL_FreeSurface(surface);
    }

    font = TTF_OpenFont("fonts/Lato-Regular.ttf", 20);

    return true;
}

void SDLRenderer::Release()
{
    for (auto texture : backgroundImages)
        SDL_DestroyTexture(texture);
    backgroundImages.clear();

    TTF_CloseFont(font);
    SDL_DestroyRenderer(handle);
}

bool SDLRenderer::StartScene(int backgroundImageIndex)
{
    SDL_RenderClear(handle);
    return SDL_RenderCopy(handle, backgroundImages[backgroundImageIndex], nullptr, nullptr) == 0;
}

bool SDLRenderer::EndScene()
{
    SDL_RenderPresent(handle);
    return true;
}

SDL_Renderer* SDLRenderer::GetHandle() const
{
    return handle;
}

bool SDLRenderer::DisplayText(const std::string& text, TextAlign textAlign, bool wrap, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const SDL_Color& color)
{
    SDL_Surface* surface;

    if (wrap)
        surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 0);
    else
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

    if(!surface)
        return false;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(handle, surface);
    if(!texture)
        return false;

    if (textAlign == TextAlign::TEXTALIGN_CENTER)
    {
        SDL_Rect destination{x+(width-surface->w)/2, y+(height-surface->h)/2, surface->w, surface->h};
        SDL_RenderCopy(handle, texture, nullptr, &destination);
    }
    else
    {
        SDL_Rect destination{x, y, surface->w, surface->h};
        SDL_RenderCopy(handle, texture, nullptr, &destination);
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return true;
}

bool SDLRenderer::DisplayTextScroll(const std::string& text, TextAlign textAlign, bool wrap, uint32_t& scrollOffset, uint32_t x, uint32_t y, uint32_t width, uint32_t height, const SDL_Color& color)
{
    SDL_Surface* surface;

    if (wrap)
        surface = TTF_RenderUTF8_Blended_Wrapped(font, text.c_str(), color, 0);
    else
        surface = TTF_RenderUTF8_Blended(font, text.c_str(), color);

    if(!surface)
        return false;

    SDL_Texture* texture = SDL_CreateTextureFromSurface(handle, surface);
    if(!texture)
        return false;

    if (textAlign == TextAlign::TEXTALIGN_CENTER)
    {
        SDL_Rect destination{x+(width-surface->w)/2, y+(height-surface->h)/2, surface->w, surface->h};
        SDL_RenderCopy(handle, texture, nullptr, &destination);
    }
    else
    {
        if (surface->h > height)
        {
            uint32_t offset{scrollOffset*4};
            uint32_t maxScrollOffset{surface->h-height};
            if (offset > maxScrollOffset)
            {
                scrollOffset = maxScrollOffset/4;
                offset = maxScrollOffset;
            }
            SDL_Rect destination{x, y, surface->w, height};
            SDL_Rect clip{0, offset, surface->w, height};
            SDL_RenderCopy(handle, texture, &clip, &destination);
        }
        else
        {
            SDL_Rect destination{x, y, surface->w, surface->h};
            SDL_RenderCopy(handle, texture, nullptr, &destination);
        }
    }

    SDL_DestroyTexture(texture);
    SDL_FreeSurface(surface);

    return true;
}