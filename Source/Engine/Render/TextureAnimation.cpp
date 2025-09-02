/*#include "TextureAnimation.h"
namespace gaia {
	bool TextureAnimation::Load(const std::string& filename, class Renderer& renderer) {
		//load json
		gaia::json::document_t document;
		if (!gaia::json::LoadFromFile(filename, document)) {
			Logger::Error("Failed to load texture animation json file: %s", filename.c_str());
			return false;
		}

		std::string texture_name;
		JSON_READ(document, texture_name);
}
*/