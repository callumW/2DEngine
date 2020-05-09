#include "TextureLoader.h"
#include "Globals.h"

#include <cassert>
#include <iostream>

TextureLoader& TextureLoader::get()
{
    static TextureLoader loader;
    return loader;
}

texture_t TextureLoader::load_texture_cached(std::string const& path)
{
    auto res = textures.find(path);

    if (res == textures.end()) {
        return add_texture(path);
    }
    else {
        return res->second;
    }
}

texture_t TextureLoader::add_texture(std::string const& path)
{
    SDL_Surface* tmp = SDL_LoadBMP(path.c_str());
    texture_t tex;

    if (tmp) {
        tex.tex = SDL_CreateTextureFromSurface(g_renderer, tmp);
        tex.width = tmp->w;
        tex.height = tmp->h;
        SDL_FreeSurface(tmp);

        textures.insert({path, tex});
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
        tex = default_tex;
    }
    return tex;
}

texture_t TextureLoader::default_texture()
{
    if (default_tex.tex == nullptr) {
        default_tex.tex = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888,
                                            SDL_TEXTUREACCESS_STATIC, 40, 40);
        SDL_SetRenderTarget(g_renderer, default_tex.tex);
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderClear(g_renderer);
        SDL_RenderDrawRect(g_renderer, nullptr);
        SDL_SetRenderTarget(g_renderer, nullptr);
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);

        default_tex.width = 40;
        default_tex.height = 40;
    }

    assert(default_tex.tex != nullptr);

    return default_tex;
}
