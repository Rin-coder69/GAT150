#pragma once

#include "Component.h"
#include "Render/TextureAnimation.h"
#include <map>

namespace gaia {
	class Animator : public Component {
	public:
		void Update(float dt) override;
		struct TextureAnimInfo {
			std::string textureAnimationName;
			res_t<TextureAnimation> textureAnimation;
		};

		int frame = 0;
		float speedMultiplier = 1.0f;
	public:
		//Animator() = default;
		Class_PROTOTYPE(Animator)
		void Start() override;
		void Play(const std::string& name, bool resetFrame = true);
		void Pause(bool pause) { m_paused = pause; }
		const std::string& getCurrentAnimationName() const { return m_currentAnimationName; }
		void Read(const json::value_t& value) override;

	private:
		float m_frameTimer = 0.0f;
		bool m_paused = false;
		std::string m_currentAnimationName;
		std::map<std::string, TextureAnimInfo> m_animations;
		class SpriteRenderer* m_spriteRenderer{ nullptr };
		TextureAnimation* m_currentAnimation{ nullptr };

	};
}