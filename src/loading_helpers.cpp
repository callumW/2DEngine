#include "loading_helpers.h"
#include "Globals.h"
#include "TextureLoader.h"

texture_t load_texture(std::string const& path)
{
    return TextureLoader::get().load_texture_cached(path);
}

texture_t load_default_texture() { return TextureLoader::get().default_texture(); }

void* tmx_load_texture(char const* path)
{
    return TextureLoader::get().tmx_load_texture_cached(path);
}
