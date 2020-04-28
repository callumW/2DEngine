#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>


class TextureLoader {
public:
    static TextureLoader& get();

    SDL_Texture* load_texture_cached(std::string const& path);

    SDL_Texture* default_texture();

    void clean_up_textures();

private:
    TextureLoader(){};
    SDL_Texture* add_texture(std::string const& path);
    std::unordered_map<std::string, SDL_Texture*> textures;

    SDL_Texture* default_tex = nullptr;
};
#endif
