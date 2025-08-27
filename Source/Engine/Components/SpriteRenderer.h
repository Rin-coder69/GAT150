#pragma once
#include "RendererComponents.h"

namespace gaia {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;

	public:

		Class_PROTOTYPE(SpriteRenderer)
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}