#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <string>
#include <memory>

class SDLWindow
{
public:

	SDLWindow(const std::string& title, std::uint32_t width, std::uint32_t height);

	bool Init();
	bool Release();

	std::string GetTitle() const;
	std::uint32_t GetWidth() const;
	std::uint32_t GetHeight() const;
	SDL_Window* GetHandle() const;

private:
	
	std::string title;
	std::uint32_t width;
	std::uint32_t height;
	SDL_Window* handle;
};

using SDLWindowPtr = std::shared_ptr<SDLWindow>;

#endif