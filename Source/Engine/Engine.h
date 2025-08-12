#pragma once
#include "core/Time.h"
#include "Core/Singleton.h"
#include "Render/Renderer.h"
#include "Audio/AudioSystem.h"
#include "Input/InputSystem.h"
#include "Render/particlesystem.h"
#include "Resources/ResourceManager.h"

#include <memory>

#define RENDERER gaia::GetEngine().GetRenderer()

namespace gaia {
	class Renderer;
	class AudioSystem;
	class InputSystem;
	class ParticleSystem;


	class Engine : public Singleton<Engine>{

	public:

		bool Initialize();
		void ShutDown();

		void Update();
		void Draw();

		Renderer& GetRenderer() const { return *m_renderer; }
		AudioSystem& GetAudio() const { return *m_audio; }
		InputSystem& GetInput() const { return *m_input; }
		ParticleSystem& GetParticleSystem() const { return *m_particleSystem; }

		Time& GetTime() { return time; }

	private:
		friend class Singleton<Engine>;
		Engine() = default;

	private:
		Time time;
		std::unique_ptr<Renderer> m_renderer;
		std::unique_ptr<AudioSystem> m_audio;
		std::unique_ptr<InputSystem> m_input;
		std::unique_ptr<ParticleSystem> m_particleSystem;
	};

	inline Engine& GetEngine() { return Engine::Instance(); }
	//inline Renderer& GetRenderer() { return GetEngine().GetRenderer(); }
}