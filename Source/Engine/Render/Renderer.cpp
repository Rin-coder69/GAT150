#include "Renderer.h"
#include "Texture.h"
#include <SDL3_ttf/SDL_ttf.h>
#include "Core/Logger.h"    

namespace gaia
{

    bool Renderer::Initialize() {
        if (!SDL_Init(SDL_INIT_VIDEO)) {
            Logger::Error("SDL_Init Error : {}", SDL_GetError());
            return false;
        }
        if(!TTF_Init()) {
           Logger::Error("TTF_Init Error {}", SDL_GetError());
            return false;
		}

        return true;

    }

   
  

    void Renderer::DrawPoint(float x, float y)
    {
		SDL_RenderPoint(renderer, x, y);
    }


    bool CreateWindow(const std::string& name, int width, int height, bool fullscreen){
        return true;
    }


    bool Renderer::CreateWindow(const std::string& name, int width, int height)    {
        window = SDL_CreateWindow(name.c_str(), width, height, 0);
		m_width = width;
		m_height = height;
    if (window == nullptr) {
        Logger::Error("SDL_CreateWindow Error {} ",SDL_GetError());
        SDL_Quit();
        return false;
    
    }

    renderer = SDL_CreateRenderer(window, NULL);
    if (renderer == nullptr) {
        Logger::Error("SDL_CreateRenderer Error {}",SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
        }

    return true;

    }

    /*void Renderer::SetColor(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColor(renderer, r, g, b, a);
    };*/

    SDL_Renderer* Renderer::GetSDLRenderer()
    {
        return renderer;
	}
    void Renderer::SetColor(float r, float g, float b, float a)
    {
        SDL_SetRenderDrawColorFloat(renderer, r, g, b, a);
    };

    void Renderer::Clear()
    {
        SDL_RenderClear(renderer);
    };

    void Renderer::Present()
    {
        SDL_RenderPresent(renderer);
    };

    void Renderer::DrawLine(float x1, float y1, float x2, float y2)
    {
        SDL_RenderLine(renderer, x1, y1, x2, y2);
    };

    void Renderer::DrawTexture(Texture& texture, float x, float y)
    {
		vec2 size = texture.GetSize();

            SDL_FRect destRect;
        destRect.x = x;
        destRect.y = y;
        destRect.w = size.x;
        destRect.h = size.y;

        SDL_RenderTexture(renderer, texture.m_texture, NULL, &destRect);
    }



    void Renderer::DrawTexture(Texture* texture, float x, float y, float angle, float scale) {

        vec2 size = texture->GetSize();

        SDL_FRect destRect;
        destRect.w = size.x * scale;
        destRect.h = size.y * scale;
        destRect.x = x - destRect.w * 0.5f;// Center the texture
		destRect.y = y - destRect.h * 0.5f;// Center the texture
       

        SDL_RenderTextureRotated(renderer, texture->m_texture, NULL, &destRect, angle, NULL, SDL_FLIP_NONE);
    }
    
    void  Renderer:: ShutDown() {
		TTF_Quit();
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }

   
}
