#include "Animator.h"
#include "SpriteRenderer.h"
#include "Render/Renderer.h"
#include "Render/TextureAnimation.h"
#include "Engine.h"
#include "../Core/StringHelper.h"
#include "EnginePCH.h"

namespace gaia {
	FACTORY_REGISTER(Animator)
		void Animator::Start()
	{
		m_sprite = owner->GetComponent<SpriteRenderer>();
		if (!m_sprite) {
			Logger::Error("Animator missing sprite renderer");
		}

		for (auto& animation : m_animations) {
			animation.second.textureAnim = Resources().Get<TextureAnimation>(animation.second.textureAnimName, GetEngine().GetRenderer());
			if (!animation.second.textureAnim) {
				Logger::Error("Failed to load texture animation: %s", animation.second.textureAnimName.c_str());
			}
			else {
				Logger::Info("Animator animation {}, texture {} loaded", animation.first, animation.second.textureAnimName);
				owner->GetComponent<gaia::Animator>()->Play("idle");
			}

		}
		auto it = m_animations.begin();

		std::string name = it->first;
		Play(name);
	}

	void Animator::Update(float dt)
	{
		if (m_pause || m_animations.empty() || !m_currentAnim.textureAnim) return;

		//update frame timer
		m_frameTimer -= dt * speedMultiplier;
		if (m_frameTimer <= 0) {
			m_frameTimer = 1.0f / m_currentAnim.textureAnim->GetFPS();
			frame++;

			if (frame >= m_currentAnim.textureAnim->GetTotalFrames()) {
				if (m_currentAnim.textureAnim->isLooping()) {
					frame = 0;
				}
				else {
					frame = m_currentAnim.textureAnim->GetTotalFrames() - 1;

				}
			}

			if (m_sprite) {
				m_sprite->textureRect = m_currentAnim.textureAnim->GetFrameRect(frame);
			}
		}
	}

	void Animator::Play(const std::string& name, bool resetFrame)
	{
		if (gaia::tolower(name) == gaia::tolower(m_currentAnimName)) return;

		auto it = m_animations.find(tolower(name));
		if (it == m_animations.end()) {
			Logger::Error("Animator could not find animation: %s", name.c_str());
			return;
		}
		m_currentAnimName = name;
		m_currentAnim = it->second;

		if (resetFrame) frame = 0;
		m_frameTimer = 1.0f / m_currentAnim.textureAnim->GetFPS();

		if (m_sprite) {
			m_sprite->texture = m_currentAnim.textureAnim->GetTexture();
			m_sprite->textureRect = m_currentAnim.textureAnim->GetFrameRect(frame);
		}
	}

	void Animator::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, frame);

		if (JSON_HAS(value, animations) && JSON_GET(value, animations).IsArray()) {
			// safe to access m_animations
			for (auto& animValue : JSON_GET(value, animations).GetArray()) {
				std::string name;
				std::string textureAnimName;
				JSON_READ_NAME(animValue, "name", name);
				JSON_READ_NAME(animValue, "texture_animation", textureAnimName);

				TextureAniminfo animInfo;
				animInfo.textureAnimName = textureAnimName;
				m_animations[tolower(name)] = animInfo;
			}
		}
	}
}
