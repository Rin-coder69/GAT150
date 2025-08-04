#include "Actor.h"
#include "Render/Renderer.h"
#include "../Render/Model.h"

void gaia::Actor::Update(float deltaTime) {

	if (destroyed) return;

	if (lifespan != 0) {
		lifespan -= deltaTime;
		destroyed = (lifespan <= 0);
	}  
	transform.position += velocity * deltaTime;
	velocity *= (1.0f / 1.0f - damping * deltaTime);

}

void gaia::Actor::Draw(class Renderer& renderer) const {
	if (m_model) {
		m_model->draw(renderer, transform);
	}
}

float gaia::Actor::GetRadius()
{
	return (m_model) ? m_model->GetRadius() * transform.scale * 0.9f  : 0;
}
