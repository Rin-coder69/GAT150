#pragma once
#include "Components/Component.h"
#include "Render/TextureAnimation.h"

namespace gaia
{
	class Animator : public Component {
	public:
		struct TextureAniminfo {
			std::string textureAnimName;
			res_t<TextureAnimation> textureAnim;
		};

		int frame = 0;
		float speedMultiplier{ 1 };

	public:
		Class_PROTOTYPE(Animator)

	void Start() override;
	void Update(float dt) override;

	void Play(const std::string& name, bool resetFrame = true);
	void Pause(bool pause) { m_pause = pause; }
	bool isPaused() const { return m_pause; }

	const std::string& GetCurrentAnimation() const { return m_currentAnimName; }

	void Read(const json::value_t& value) override;
	private:
		float m_frameTimer = 0;
		bool m_pause = false;

		std::string m_currentAnimName;
		TextureAniminfo m_currentAnim;

		std::map<std::string, TextureAniminfo> m_animations;
		class SpriteRenderer* m_sprite{ nullptr };
	};
}