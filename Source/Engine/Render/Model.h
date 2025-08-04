#pragma once
#include "../Engine/Math/vector2.h"
#include "../Engine/Math/vector3.h"
#include "../Engine/Math/transform.h"
#include <vector>


namespace gaia {
	class Model{
	public:
		Model() = default;
		Model(const std::vector<gaia::vec2>& points, const vec3& color):
			points{points},
			color{ color } {
			CalculateRadius();
		}
		void draw(class Renderer& renderer, const vec2& position, float roatation, float scale);
		void draw(class Renderer& renderer, const Transform& transform);

		float GetRadius() { return m_radius; }
	private:
		void CalculateRadius();

	private:
		float m_radius{ 0 };
		std::vector<gaia::vec2> points;
		vec3 color{ 1.0f, 1.0f, 1.0f }; // Default color white
		};
} 