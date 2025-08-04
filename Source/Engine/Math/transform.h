#pragma once
#include "../Engine/Math/vector2.h"
namespace gaia
{
	struct Transform {
		vec2 position{ 0,0 };
		float rotation = 0; // in radians
		float scale = 1; // uniform scale factor

		Transform() = default;
		Transform(const vec2& pos, float rot, float scl)
			: position{ pos }, rotation{ rot }, scale{ scl }
		{
		}
	};
}