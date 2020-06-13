#ifndef LOADING_HELPERS_H
#define LOADING_HELPERS_H
#include <string>

#include "Texture.h"

texture_t load_texture(std::string const& path);
texture_t load_default_texture();

// Specifically for usage with libtmx when loading tilemaps
void* tmx_load_texture(char const* path);

#endif
