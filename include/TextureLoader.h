#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H
#include <SDL2/SDL.h>
#include <json/json.h>

#include <string>
#include <unordered_map>


#include "Animation.h"
#include "Texture.h"


class TextureLoader {
public:
    static TextureLoader& get();

    texture_t load_texture_cached(std::string const& path);

    texture_t default_texture();

    bool load_animation_frames(std::string const& path, animation_t& animation);

    void clean_up_textures();

private:
    TextureLoader() = default;
    texture_t add_texture(std::string const& path);
    bool create_animation_frames(Json::Value& root, std::vector<animation_frame_t>& animation);
    bool is_valid_animation(Json::Value& root);

    std::unordered_map<std::string, texture_t> textures;

    texture_t default_tex = {};
};
#endif
