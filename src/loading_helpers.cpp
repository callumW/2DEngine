#include "loading_helpers.h"
#include "Globals.h"
#include "TextureLoader.h"

SDL_Texture* load_texture(std::string const& path)
{
    return TextureLoader::get().load_texture_cached(path);
}

SDL_Texture* load_default_texture() { return TextureLoader::get().default_texture(); }
