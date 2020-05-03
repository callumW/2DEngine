#ifndef UI_SYSTEM_H
#define UI_SYSTEM_H
#include <SDL2/SDL.h>
#include <SDL2_ttf/SDL_ttf.h>

#include <string>
#include <utility>
#include <vector>


class UISystem {
public:
    static UISystem& get();

    void add_static_text(SDL_Rect location, std::string const& str);
    void add_static_text(SDL_Point location, std::string const& str);

    void add_dynamic_text(SDL_Rect location, std::string const& str);
    void add_dynamic_text(SDL_Point location, std::string const& str);

    void render();


    void deinit();

private:
    typedef std::pair<SDL_Rect, SDL_Texture*> text_entity;

    UISystem();

    void render_entity(text_entity const& e);
    void deinit_entity(text_entity const& e);

    SDL_Rect calculate_rect(SDL_Point p, std::string const& str);

    SDL_Texture* load_text(std::string const& str);

    void clear_dynamic_text();

    TTF_Font* font;

    std::vector<text_entity> static_text_entities;

    std::vector<text_entity> dynamic_text_entities;
};
#endif
