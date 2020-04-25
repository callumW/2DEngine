#include "TextureLoader.h"
#include "Globals.h"

#include <iostream>

SDL_Texture* TextureLoader::load_texture_cached(std::string const& path)
{
    auto res = textures.find(path);

    if (res == textures.end()) {
        return add_texture(path);
    }
    else {
        return res->second;
    }
}

SDL_Texture* TextureLoader::add_texture(std::string const& path)
{
    SDL_Texture* ret = nullptr;
    SDL_Surface* tmp = SDL_LoadBMP(path.c_str());

    if (tmp) {
        ret = SDL_CreateTextureFromSurface(g_renderer, tmp);
        SDL_FreeSurface(tmp);

        textures.insert({path, ret});
    }
    else {
        std::cout << "Failed to load texture: " << path << std::endl;
        ret = default_tex;
    }
    return ret;
}

SDL_Texture* TextureLoader::default_texture()
{
    if (default_tex == nullptr) {
        default_tex = SDL_CreateTexture(g_renderer, SDL_PIXELFORMAT_RGBA8888,
                                        SDL_TEXTUREACCESS_STATIC, 40, 40);
        SDL_SetRenderTarget(g_renderer, default_tex);
        SDL_SetRenderDrawColor(g_renderer, 255, 0, 0, 255);
        SDL_RenderClear(g_renderer);
        SDL_RenderDrawRect(g_renderer, nullptr);
        SDL_SetRenderTarget(g_renderer, nullptr);
        SDL_SetRenderDrawColor(g_renderer, 255, 255, 255, 255);
    }

    return default_tex;
}
