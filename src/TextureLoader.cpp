#include "TextureLoader.h"
#include "Globals.h"
#include "file_utils.h"

#include <SDL2_image/SDL_image.h>

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
    SDL_Surface* tmp = IMG_Load(path.c_str());
    texture_t tex = {};

    if (tmp) {
        tex.tex = SDL_CreateTextureFromSurface(g_renderer, tmp);
        tex.src_rect.w = tmp->w;
        tex.src_rect.h = tmp->h;
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

        default_tex.src_rect.w = 40;
        default_tex.src_rect.h = 40;
    }

    assert(default_tex.tex != nullptr);

    return default_tex;
}

bool TextureLoader::load_animation_frames(std::string const& path, animation_t& animation)
{
    auto file_contents = read_file(path);
    if (file_contents.first == nullptr) {
        std::cout << "Failed to load animation frames from: " << path << std::endl;
        return false;
    }

    Json::CharReaderBuilder reader_builder;
    Json::CharReader* reader = reader_builder.newCharReader();
    Json::Value root;
    std::string err;
    if (!reader->parse(file_contents.first.get(), file_contents.first.get() + file_contents.second,
                       &root, &err)) {
        std::cout << "Failed to parse animation frames file (" << path << "): " << err << std::endl;
        return false;
    }
    else {
        assert(is_valid_animation(root));
        if (create_animation_frames(root, animation.frames)) {
            std::string texture_path;

            auto pos = path.rfind("/");
            assert(pos != std::string::npos);

            texture_path = path.substr(0, pos + 1) + root["meta"]["image"].asString();
            auto tex = load_texture_cached(texture_path);
            assert(tex.tex != nullptr);

            for (auto& frame : animation.frames) {
                animation.total_duration += frame.duration;
                frame.texture.tex = tex.tex;
            }
        }
        else {
            std::cout << "Failed to create animation frames" << std::endl;
            return false;
        }
    }
    delete reader;
    return true;
}

bool TextureLoader::create_animation_frames(Json::Value& root,
                                            std::vector<animation_frame_t>& animation)
{
    auto frames = root["frames"];
    int num_frames = frames.size();
    animation.resize(num_frames);

    int sheet_width = root["meta"]["size"]["w"].asInt();

    size_t i = 0;
    for (auto& frame : frames) {
        float duration = frame["duration"].asFloat() / 1000.0f;
        SDL_Rect src_rect = {frame["frame"]["x"].asInt(), frame["frame"]["y"].asInt(),
                             frame["spriteSourceSize"]["w"].asInt(),
                             frame["spriteSourceSize"]["h"].asInt()};

        i = src_rect.x / src_rect.w + (src_rect.y / src_rect.h * (sheet_width / src_rect.w));

        assert(i < frames.size());
        animation[i].duration = duration;
        animation[i].texture.src_rect = src_rect;
    }

    return true;
}

bool TextureLoader::is_valid_animation(Json::Value& root)
{

    if (root.isMember("meta")) {
        auto& meta = root["meta"];
        if (meta.isMember("size")) {
            auto& size = meta["size"];
            if (!size.isMember("w") || !size.isMember("h")) {
                return false;
            }
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }

    // Needs frames object with at least one frame
    // frame needs to include frame element with x, y, w, h elements
    if (root.isMember("frames")) {
        auto frames = root["frames"];
        if (frames.isObject() && frames.size() > 0) {
            for (auto& frame : frames) {
                if (frame.isMember("frame")) {
                    auto frame_dim = frame["frame"];
                    if (!frame_dim.isMember("x") || !frame_dim.isMember("y") ||
                        !frame_dim.isMember("w") || !frame_dim.isMember("h")) {
                        return false;
                    }
                }
                else {
                    return false;
                }

                if (!frame.isMember("duration")) {
                    return false;
                }

                if (frame.isMember("spriteSourceSize")) {
                    auto source_size = frame["spriteSourceSize"];
                    if (!source_size.isMember("x") || !source_size.isMember("y") ||
                        !source_size.isMember("w") || !source_size.isMember("h")) {
                        return false;
                    }
                }
            }
        }
        else {
            return false;
        }
    }
    else {
        std::cout << "Missing frames element" << std::endl;
        return false;
    }

    return true;
}
