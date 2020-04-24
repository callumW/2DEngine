#include "loading_helpers.h"
#include "Globals.h"
#include "TextureLoader.h"

TextureLoader texture_loader;

SDL_Texture* load_texture(std::string const& path)
{
    return texture_loader.load_texture_cached(path);
}

SDL_Texture* load_default_texture() { return texture_loader.default_texture(); }
