#include "Actor.h"

#include "Render/Renderer.h"
#include "../Render/Model.h"
#include "Components/Component.h"
#include "Components/RendererComponents.h"


void gaia::Actor::Update(float deltaTime) {
	FACTORY_REGISTER(Actor)

	if (destroyed) return;

	if (lifespan != 0) {
		lifespan -= deltaTime;
		destroyed = (lifespan <= 0);
	}  

	for(auto& component : m_components) {
		if (component->active)	component->Update(deltaTime);
	}
	
	
}

void gaia::Actor::Draw(Renderer& renderer) const {
	if (destroyed) return;

	//update all components that are active
	for (auto& component : m_components) {
		if (component->active) {
			auto rendererComponent = dynamic_cast<RendererComponent*>(component.get());
			if (rendererComponent) {
				rendererComponent->Draw(renderer);
			}

		}
	}
}
float gaia::Actor::GetRadius()
{
	return (m_texture) ? m_texture->GetSize().length() * 0.5f * transform.scale * 0.9f : 0;
}

void gaia::Actor::AddComponent(std::unique_ptr<Component> component)
{
	component->owner = this;
	m_components.push_back(std::move(component));
}

void gaia::Actor::Read(const json::value_t& value)
{
	Object::Read(value);

	JSON_READ(value, tag);
	JSON_READ(value, lifespan);

	if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

	//read component
	if (JSON_HAS(value, Components)) {
		for (auto& ComponentValue : JSON_GET(value, Components).GetArray()) {
			std::string type;
			JSON_READ(ComponentValue,type);

			auto component = Factory::Instance().Create(type);
			component->Read(ComponentValue);
			//AddComponent(std::move(component));
		}
	}
}

