#include "TextureAnimation.h"
namespace gaia {
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		//load json
		gaia::json::document_t document;
		if (!gaia::json::Load(filename, document)) {
			Logger::Error("Failed to load texture animation json file: %s", filename.c_str());
			return false;
		}

		std::string texture_name;
		JSON_READ(document, texture_name);

		//load texture
		m_texture = Resources().Get<Texture>(texture_name, renderer);
		if (!m_texture) {
			Logger::Error("Failed to load texture for texture animation: %s", texture_name.c_str());
		}

		JSON_READ_NAME(document, "columns", m_cols);
		JSON_READ_NAME(document, "rows", m_rows);
		JSON_READ_NAME(document, "total_frames", totalFrames);
		JSON_READ_NAME(document, "start_frame", startFrame);
		JSON_READ_NAME(document, "fps", fps);
		JSON_READ_NAME(document, "loop", m_loop);
		return true;
	}

	vec2 TextureAnimation::GetSize() const {
		vec2 size = m_texture->GetSize();

		return { size.x / m_cols, size.y / m_rows };
	}
	rect TextureAnimation::GetFrameRect(int frame) const {
		if (!isValidFrame(frame)) {
			Logger::Warning("Frame is outside bounds{}: {}", frame, totalFrames);
			frame = 0;
		}
		rect frameRect;
		vec2 size = GetSize();

		frameRect.w = size.x;
		frameRect.h = size.y;
		frameRect.x = ((startFrame + frame) % m_cols) * frameRect.w;
		frameRect.y = ((startFrame + frame) / m_cols) * frameRect.h;

		return frameRect;
	}
}
