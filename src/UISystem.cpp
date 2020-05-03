#include "UISystem.h"
#include "Globals.h"

#include <iostream>

UISystem& UISystem::get()
{
    static UISystem sys;
    return sys;
}

void UISystem::add_text(SDL_Rect location, std::string const& str)
{
    text_entities.push_back({location, load_text(str)});
}

void UISystem::render()
{
    for (auto& entity : text_entities) {
        SDL_RenderCopyEx(g_renderer, entity.second, nullptr, &entity.first, 0.0, nullptr,
                         SDL_FLIP_NONE);
    }
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
    for (auto& entity : text_entities) {
        SDL_DestroyTexture(entity.second);
    }
    text_entities.clear();

    TTF_CloseFont(font);
    font = nullptr;
}
