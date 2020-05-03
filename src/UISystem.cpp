#include "UISystem.h"
#include "Globals.h"

#include <iostream>

UISystem& UISystem::get()
{
    static UISystem sys;
    return sys;
}

void UISystem::add_static_text(SDL_Point location, std::string const& str)
{
    SDL_Rect text_location;
    text_location.x = location.x;
    text_location.y = location.y;

    text_location.w = str.size() * 16;
    text_location.h = 32;
    add_static_text(text_location, str);
}

void UISystem::add_static_text(SDL_Rect location, std::string const& str)
{
    static_text_entities.push_back({location, load_text(str)});
}

void UISystem::render()
{
    for (auto& entity : static_text_entities) {
        SDL_RenderCopyEx(g_renderer, entity.second, nullptr, &entity.first, 0.0, nullptr,
                         SDL_FLIP_NONE);
    }

    for (auto& entity : dynamic_text_entities) {
        SDL_RenderCopyEx(g_renderer, entity.second, nullptr, &entity.first, 0.0, nullptr,
                         SDL_FLIP_NONE);
    }
    clear_dynamic_text();
}

SDL_Texture* UISystem::load_text(std::string const& str)
{
    SDL_Texture* tex = nullptr;
    SDL_Surface* tmp_surface = TTF_RenderUTF8_Solid(font, str.c_str(), {0, 0, 0});

    if (font != nullptr && tmp_surface != nullptr) {
        tex = SDL_CreateTextureFromSurface(g_renderer, tmp_surface);
        SDL_FreeSurface(tmp_surface);
    }

    return tex;
}

UISystem::UISystem()
{
    font = TTF_OpenFont("./assets/SpaceMono-Regular.ttf", 16);
    if (font == nullptr) {
        std::cout << "Failed to load font, KABOOM!" << std::endl;
        exit(1);
    }
}

void UISystem::deinit()
{
    for (auto& entity : static_text_entities) {
        SDL_DestroyTexture(entity.second);
    }
    static_text_entities.clear();

    TTF_CloseFont(font);
    font = nullptr;
}

void UISystem::clear_dynamic_text()
{
    for (auto& entity : dynamic_text_entities) {
        SDL_DestroyTexture(entity.second);
    }
    dynamic_text_entities.clear();
}

void UISystem::add_dynamic_text(SDL_Rect location, std::string const& str)
{
    dynamic_text_entities.push_back({location, load_text(str)});
}

void UISystem::add_dynamic_text(SDL_Point location, std::string const& str)
{
    SDL_Rect text_location;
    text_location.x = location.x;
    text_location.y = location.y;

    text_location.w = str.size() * 16;
    text_location.h = 32;
    add_dynamic_text(text_location, str);
}
