#pragma once
#include "Renderer.h"
#include <iostream>
#include <SDL3/SDL.h>
struct TTF_Font;
namespace gaia
{
	class Font {
	public:
		Font() = default;
		~Font();

		bool Load(const std::string& name, float fontSize);

	private:
		friend class Text;

		TTF_Font* m_ttfFont{ nullptr };
	};
}