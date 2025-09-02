#pragma once
namespace gaia {
	class Texture;

	class TextureAnimation : public Resource {
	public:
		TextureAnimation() = default;
		~TextureAnimation() = default;

		bool Load(const std::string& filename, class Renderer& renderer);

		vec2 GetSize() const;

		rect GetFrameRect(int frame) const;
		int GetTotalFrames() const { return totalFrames; }
		float GetFPS() const { return fps; }
		bool isValidFrame(int frame) const { return frame >= 0 && frame < totalFrames; }
		bool isLooping() const { return m_loop; }

		res_t<Texture> GetTexture() const { return m_texture; }

	private:
		int m_rows = 0;
		int m_cols = 0;
		int totalFrames = 0;
		int startFrame = 0;
		float fps = 0;
		bool m_loop = true;

		res_t<Texture> m_texture;
	};
	