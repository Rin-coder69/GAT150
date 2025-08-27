#pragma once
#include "RendererComponents.h"

namespace gaia {
		class MeshRenderer : public RendererComponent {
	public:
		std::string meshName;
	public:
		Class_PROTOTYPE(MeshRenderer)

		void Update(float deltatime) override;
		void Draw(Renderer& renderer) override;
		};
}