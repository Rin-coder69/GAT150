#include "particlesystem.h"
#include "Renderer.h"

namespace gaia {
	bool ParticleSystem::Initialize(int poolSize) {
		//reserve particles in pool
		m_particles.resize(poolSize);

		return true;
	}


	void ParticleSystem::Update(float deltaTime) {
	for(auto& particle : m_particles){
		if(particle.active) {
			particle.lifespan -= deltaTime;
			particle.position += particle.velocity * deltaTime;
			//particle.previousPosition = particle.position;
			particle.active = (particle.lifespan > 0);
			}
		}
	}

	void ParticleSystem::ShutDown() {
		m_particles.clear();

	}
	void ParticleSystem::Draw(class Renderer& renderer) {
		for (auto& particle : m_particles) {
			if (particle.active) {
				renderer.SetColor(particle.color.r, particle.color.g, particle.color.b);
				renderer.DrawPoint(particle.position.x, particle.position.y);
			}
		}
	}
	 
	void ParticleSystem::AddParticle(const Particle& particle) {
		Particle* pParticle = GetFreeParticle();
		if (pParticle) {
			*pParticle = particle;
			pParticle->active = true;
			pParticle->lifespan = particle.lifespan;
			pParticle->position = particle.position;
			pParticle->velocity = particle.velocity;
			pParticle->color = particle.color;
		}
		else {
			std::cerr << "No free particles available!" << std::endl;
		}
	}

	Particle* ParticleSystem::GetFreeParticle()
	{
		for (auto& particle : m_particles) {
			if (!particle.active) return &particle;
				return &particle;
			}
		return nullptr;
		}
		
	}


	