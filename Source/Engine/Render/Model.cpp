#include "Model.h"
#include "Render/Renderer.h"

namespace gaia {
	void Model::draw(Renderer& renderer, const vec2& position, float roatation, float scale) {

		if (points.empty()) return; // No points to draw
		// Set the color for the model
		renderer.SetColor(color.x, color.y, color.b);

		for (int i = 0; i < points.size() - 1; i++) {
			//points[i].Rotate(roatation);
			vec2 p1 = points[i].Rotate(gaia::math::degToRad(roatation)) * scale + position;
			vec2 p2 = points[i + 1].Rotate(gaia::math::degToRad(roatation)) * scale + position;

			renderer.DrawLine(p1.x, p1.y, p2.x, p2.y);
		}
	}
	void Model::draw(Renderer& renderer, const Transform& transform)
	{
		draw(renderer, transform.position, transform.rotation, transform.scale);
	}

	void Model::CalculateRadius() {
		m_radius = 0;
		for (auto& point : points) {
			float length = point.length();
			if (length > m_radius)m_radius = length;
		}
	}
}
