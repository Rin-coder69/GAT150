#pragma once

#include "Components/Component.h"
#include "Render/TextureAnimation.h"

namespace gaia{
	class Animator : public Component {
	public:
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
		void Update(float dt) override;
		void Play(const std::string& name, bool resetFrame = true);
		void Pause(bool pause) { m_paused = pause;}
		const std::string& getCurrentAnimationName() const { return m_currentAnimationName; }
		void read(const Json::value_t& value) override;
	private:
		float m_frameTimer = 0.0f;
		bool m_paused = false;
		std::string m_currentAnimationName;
		TextureAnimInfo m_currentAnimation;
		std::map<std::string, TextureAnimInfo> m_animations;
		class SpriteRenderer* m_spriteRenderer{ nullptr };
		TextureAnimation* m_currentAnimation{ nullptr };
	};
}