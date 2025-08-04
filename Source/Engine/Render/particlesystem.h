#pragma once
#include <vector>
#include "Math/vector3.h"
#include "Math/vector2.h"
namespace gaia{
	struct Particle {
		bool active{ false };
		vec2 position;
		vec2 velocity;

		vec3 color;

		float lifespan{ 1.0f };
	};
	class ParticleSystem {
	public:
		ParticleSystem() = default;
		~ParticleSystem() = default;

		bool Initialize(int poolSize = 1000);
		
		void ShutDown();

		void Update(float deltaTime);

		void Draw(class Renderer& renderer);


		void AddParticle(const Particle& particle);
	private:
		Particle* GetFreeParticle();
	private:
		std::vector<Particle>m_particles;
	};
} // namespace gaia