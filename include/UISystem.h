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

    void render();


    void deinit();

private:
    UISystem();

    SDL_Texture* load_text(std::string const& str);

    TTF_Font* font;

    typedef std::pair<SDL_Rect, SDL_Texture*> text_entity;
    std::vector<text_entity> static_text_entities;
};
#endif
