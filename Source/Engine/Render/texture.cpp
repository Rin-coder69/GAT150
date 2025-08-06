#include "Texture.h"
#include "Renderer.h"
#include <cstring>
#include <SDL3_image/SDL_image.h>

namespace gaia
{


    Texture::~Texture()
    {
        // if texture exists, destroy texture
        if (!m_texture) SDL_DestroyTexture(m_texture);
    }

    bool Texture::Load(const std::string& filename, Renderer& renderer)
    {
		
        // load image onto surface
        SDL_Surface* surface = IMG_Load(filename.c_str());
        if (!surface)
        {
            std::cerr << "Could not load image: " << filename << std::endl;
            return false;
        }
        // create texture from surface, texture is a friend class of renderer
        m_texture =  static_cast<SDL_Texture*>(SDL_CreateTextureFromSurface (renderer.renderer, surface));
        SDL_DestroySurface(surface);
        if (!m_texture)
        {
            std::cerr << "Could not create texture: " << filename << std::endl;
            return false;
        }
        return true;
    }
    vec2 Texture::GetSize()
    {
        // https://wiki.libsdl.org/SDL3/SDL_GetTextureSize
		float width, height;
		SDL_GetTextureSize(m_texture, &width, &height);
		return{ width, height };
    }
}