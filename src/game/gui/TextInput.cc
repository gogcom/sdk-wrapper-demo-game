#include "TextInput.h"

#include <SDL2_gfxPrimitives.h>

TextInput::TextInput(const std::string& _caption, uint32_t _x, uint32_t _y, uint32_t _width, uint32_t _height, const GUIAction& _action)
        : text(_caption)
        , x{_x}
        , y{_y}
        , width{_width}
        , height{_height}
        , action{_action}
{
    SDL_SetHint(SDL_HINT_IME_SHOW_UI, "1");
    SDL_Rect textInputRect{x+8, y+12, width-8, height-8};
    SDL_SetTextInputRect(&textInputRect);
}

bool TextInput::IsPointInside(std::uint32_t _x, std::uint32_t _y)
{
    return _x > x && _x < x + width
        && _y > y && _y < y + height;
}

void TextInput::OnMouseDown(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
    {
        isFocused = false;
        StopTextInput();
        return;
    }

    isFocused = true;
    StartTextInput();
}

void TextInput::OnMouseMotion(std::uint32_t x, std::uint32_t y)
{
    if (!IsPointInside(x, y))
        return;
}

void TextInput::OnKeyDown(SDL_Keysym key)
{
    if (isFocused)
    {
        if (!done)
        {
            switch (key.sym) {
                case SDLK_RETURN:
                case SDLK_ESCAPE:
                    StopTextInput();
                    done = SDL_TRUE;
                    action();
                    break;
                case SDLK_BACKSPACE:
                    if (text.empty())
                        break;
                    if (!markedText.empty())
                    {
                        text.erase(cursor-selection_len, cursor);
                        break;
                    }
                    text.pop_back();
                    break;
                case SDLK_c:
                    if (SDL_GetModState() & KMOD_CTRL)
                    {
                        SDL_SetClipboardText(text.c_str());
                        break;
                    }
                case SDLK_v:
                    if (SDL_GetModState() & KMOD_CTRL)
                    {
                        text = SDL_GetClipboardText();
                        break;
                    }
                case SDLK_LEFT:
                    if (cursor <= 0)
                        break;
                    // SDL_Log("Cursor--");
                    cursor--;
                    break;
                case SDLK_RIGHT:
                    if (cursor >= text.length())
                        break;
                    // SDL_Log("Cursor++");
                    cursor++;
                    break;
            }
        }
    }
}

void TextInput::OnTextInput(SDL_TextInputEvent inputEvent)
{
    if (isFocused)
    {
        if (!done)
        {
            if (!(SDL_GetModState() & KMOD_CTRL && (inputEvent.text[ 0 ] == 'c' || inputEvent.text[ 0 ] == 'C' || inputEvent.text[ 0 ] == 'v' || inputEvent.text[ 0 ] == 'V')))
                text.append(inputEvent.text);
        }
    }
}

void TextInput::OnTextEditing(SDL_TextEditingEvent editingEvent)
{
    if (isFocused)
    {
        if (!done)
        {
            markedText = editingEvent.text;
            cursor = editingEvent.start;
            selection_len = editingEvent.length;
        }
    }
    SDL_Log("%d", cursor);
}

bool TextInput::DrawRoundedBox(SDL_Renderer* renderer, SDL_Rect rect, uint32_t radius, SDL_Color color)
{
    return roundedBoxRGBA(renderer, rect.x, rect.y, rect.w, rect.h, radius, color.r, color.g, color.b, color.a) == 0;
}

bool TextInput::Display(const SDLRendererPtr& renderer)
{
    // const SDL_Rect rectOutline{x, y, width, height};
    // const SDL_Rect rectInside{x+4, y+4, width-8, height-8};
    // SDL_Color color{0,0,0,255};

    if (isFocused)
    {
        roundedBoxRGBA(renderer->GetHandle(), x, y, x+width, y+height, 5, 255, 255, 255, 255);
        roundedBoxRGBA(renderer->GetHandle(), x+8, y+8, x+width-8, y+height-8, 5, 108, 122, 137, 255);
        // DrawRoundedBox(renderer->GetHandle(), rectOutline, 5, {255,255,255,255});
        // color = {108, 122, 137, 255};
    }
    else
    {
        roundedBoxRGBA(renderer->GetHandle(), x, y, x+width, y+height, 5, 0, 0, 0, 255);
        roundedBoxRGBA(renderer->GetHandle(), x+8, y+8, x+width-8, y+height-8, 5, 236, 236, 236, 255);
        // DrawRoundedBox(renderer->GetHandle(), rectOutline, 5, {0,0,0,255});
        // color = {236, 236, 236, 255};
    }

    // roundedBoxRGBA(renderer->GetHandle(), x+4, y+4, width-8, height-8, 5, 0, 0, 0, 255);
    // DrawRoundedBox(renderer->GetHandle(), rectInside, 5, color);

    renderer->DisplayText(text, TextAlign::TEXTALIGN_DEFAULT, false, x+8, y+12, width-8, height-8, {0, 0, 0, 255});
    // renderer->DisplayTextWithCursor(text, cursor, selection_len, x, y, width, height, {0, 0, 0, 255});
    
    return true;
}
