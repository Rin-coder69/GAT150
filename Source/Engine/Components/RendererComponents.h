#pragma once
#include "Component.h"

namespace gaia
{
	class RendererComponent : public Component
	{
	public:
		virtual void Draw(class Renderer& renderer) = 0;
	};
}