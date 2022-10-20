#ifndef TEXT_INPUT_H
#define TEXT_INPUT_H

#include <engine/SDLRenderer.h>
#include <string>
#include <functional>

using GUIAction = std::function<void()>;

class TextInput
{
public:

    TextInput(
        const std::string& caption,
        uint32_t x,
        uint32_t y,
        uint32_t width,
        uint32_t height,
        const GUIAction& _action);

    void OnMouseDown(std::uint32_t x, std::uint32_t y);
    void OnMouseMotion(std::uint32_t x, std::uint32_t y);
    void OnKeyDown(SDL_Keysym key);
    void OnTextInput(SDL_TextInputEvent inputEvent);
	void OnTextEditing(SDL_TextEditingEvent editingEvent);

    bool Display(const SDLRendererPtr& renderer);
    bool IsPointInside(std::uint32_t x, std::uint32_t y);
    bool DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color);
    void StartTextInput()
    {
        SDL_StartTextInput();
        textInputEnabled = true;
    }
    void StopTextInput()
    {
        SDL_StopTextInput();
        textInputEnabled = false;
    }
    std::string ReturnInputText()
    {
        return text;
    }

private:

    GUIAction action;
    const uint32_t x, y, width, height;

    std::string text;
    std::string markedText;
    Sint32 cursor{0};
    Sint32 selection_len{0};
    SDL_bool done{SDL_FALSE};
    bool textInputEnabled{false};
    bool isFocused{false};
    SDL_Event event;
};

using TextInputPtr = std::shared_ptr<TextInput>;

#endif