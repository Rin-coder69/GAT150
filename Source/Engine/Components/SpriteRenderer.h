#pragma once
#include "RendererComponents.h"

namespace gaia {
	class SpriteRenderer : public RendererComponent {
	public:
		std::string textureName;
		res_t<Texture> texture;

	public:

		Class_PROTOTYPE(SpriteRenderer)
		void Start() override;
		void Update(float dt) override;
		void Draw(Renderer& renderer) override;

		void Read(const json::value_t& value) override;
	};
}