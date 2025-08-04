#pragma once
#include "Renderer.h"
#include "Font.h"
#include "../Math/vector3.h"
#include <string>
#include <memory>

struct SDL_Texture;
namespace gaia{
	class Text {
	public:
		Text() = default;
		Text(std::shared_ptr<class Font> font) : m_font{ font } {}
		~Text();

		bool Create(Renderer& renderer, const std::string& text, const vec3& color);
		void Draw(Renderer& renderer, float x, float y);

	private:
		std::shared_ptr<class Font> m_font{ nullptr };
		SDL_Texture* m_texture{ nullptr };
		friend class Renderer;
	};
}
