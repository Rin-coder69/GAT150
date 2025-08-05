#include "Math/vector2.h"
#include <string>
namespace gaia
{

	class Texture
	{
	public:
		Texture() = default;
		~Texture();

		bool Load(const std::string& filename, class Renderer& renderer);
		vec2 GetSize();
		friend class Renderer;

	private:
		struct SDL_Texture* m_texture{ nullptr }; // Pointer to the SDL texture
	};
}