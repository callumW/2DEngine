#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include <SDL2/SDL.h>

#include <string>
#include <unordered_map>


#include "Texture.h"


class TextureLoader {
public:
    static TextureLoader& get();

    texture_t load_texture_cached(std::string const& path);

    texture_t default_texture();

    void clean_up_textures();

private:
    TextureLoader() = default;
    texture_t add_texture(std::string const& path);
    std::unordered_map<std::string, texture_t> textures;

    texture_t default_tex = {};
};
#endif
