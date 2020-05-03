#include "UISystem.h"
#include "Globals.h"

#include <algorithm>
#include <functional>
#include <iostream>

UISystem& UISystem::get()
{
    static UISystem sys;
    return sys;
}

void UISystem::add_static_text(SDL_Point location, std::string const& str)
{
    add_static_text(calculate_rect(location, str), str);
}

void UISystem::add_static_text(SDL_Rect location, std::string const& str)
{
    static_text_entities.push_back({location, load_text(str)});
}

void UISystem::render()
{
    static std::function<void(text_entity const&)> render_ent =
        std::bind(&UISystem::render_entity, this, std::placeholders::_1);

    std::for_each(static_text_entities.begin(), static_text_entities.end(), render_ent);

    std::for_each(dynamic_text_entities.begin(), dynamic_text_entities.end(), render_ent);

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
    static std::function<void(text_entity const&)> destroy =
        std::bind(&UISystem::deinit_entity, this, std::placeholders::_1);

    std::for_each(static_text_entities.begin(), static_text_entities.end(), destroy);

    dynamic_text_entities.clear();
}

void UISystem::add_dynamic_text(SDL_Rect location, std::string const& str)
{
    dynamic_text_entities.push_back({location, load_text(str)});
}

void UISystem::add_dynamic_text(SDL_Point location, std::string const& str)
{
    add_dynamic_text(calculate_rect(location, str), str);
}

void UISystem::render_entity(text_entity const& e)
{
    SDL_RenderCopyEx(g_renderer, e.second, nullptr, &e.first, 0.0, nullptr, SDL_FLIP_NONE);
}

void UISystem::deinit_entity(text_entity const& e) { SDL_DestroyTexture(e.second); }

SDL_Rect UISystem::calculate_rect(SDL_Point p, std::string const& str)
{
    return {p.x, p.y, static_cast<int>(str.size() * 20), 32};
}
