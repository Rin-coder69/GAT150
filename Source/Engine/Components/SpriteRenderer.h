#pragma once
#include "RendererComponents.h"

namespace gaia {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;
	};
}