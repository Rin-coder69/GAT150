#pragma once
#include <SDL3/SDL.h>
#include <iostream>

namespace gaia
{
	// Forward declaration of the Text class
	
	
	class Renderer {
	public:
		Renderer() = default;

		bool Initialize();


		void DrawPoint(float x, float y);

		void ShutDown();

		SDL_Renderer* GetSDLRenderer();

		bool CreateWindow(const std::string& name, int width, int height);

		int GetWidth() {
			return m_width;
		}

		int GetHeight() {
			return m_height;
		}
		void DrawTexture(class Texture* texture, float x, float y, float angle);

		void Clear();

		void Present();

		void DrawLine(float x1, float y1, float x2, float y2);

		void SetColor(float r, float g, float b, float a = 255);
		friend class Text;
		friend class Texture;
	private:
		SDL_Window* window = nullptr;//<---member variable for the SDL window
		SDL_Renderer* renderer = nullptr;//<---member variable for the SDL renderer 
		int m_width{ 800 }; // Default width
		int m_height{ 600 }; // Default height
		
		
	};
};