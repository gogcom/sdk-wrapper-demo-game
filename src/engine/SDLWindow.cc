#include "SDLWindow.h"

SDLWindow::SDLWindow(const std::string& _title, std::uint32_t _width, std::uint32_t _height)
	: title(_title)
	, width(_width)
	, height(_height)
{
}

bool SDLWindow::Init()
{
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0)
		return false;

	handle = SDL_CreateWindow(
		title.c_str(),
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width,
		height,
		SDL_WINDOW_SHOWN);

	if (!handle)
		return false;

	if (TTF_Init() != 0)
		return false;

	return true;
}

bool SDLWindow::Release()
{
	TTF_Quit();
	SDL_DestroyWindow(handle);
	SDL_Quit();
	return true;
}

std::string SDLWindow::GetTitle() const
{
	return title;
}

std::uint32_t SDLWindow::GetWidth() const
{
	return width;
}

std::uint32_t SDLWindow::GetHeight() const
{
	return height;
}

SDL_Window* SDLWindow::GetHandle() const
{
	return handle;
}