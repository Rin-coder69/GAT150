#include "Actor.h"
#include "Render/Renderer.h"
#include "../Render/Model.h"
#include "Components/Component.h"
#include "Components/RendererComponents.h"
namespace gaia {
	FACTORY_REGISTER(Actor)

		Actor::Actor(const Actor& other) :
		Object{ other },
		tag{ other.tag },
		lifespan{ other.lifespan },
		transform{ other.transform }
	{
		for (auto& component : other.m_components) {
			auto clone = std::unique_ptr<Component>(dynamic_cast<Component*>(component->Clone().release()));
			AddComponent(std::move(clone));
		}
	}
	void Actor::Start() {
		for (auto& component : m_components) {
			if (component->active)	component->Start();
		}
	}
	void Actor::Destroyed() {
		for (auto& component : m_components) {
			if (component->active)	component->Destroyed();
		}
	}

	void Actor::Update(float deltaTime) {

		if (destroyed) return;

		if (lifespan != 0) {
			lifespan -= deltaTime;
			destroyed = (lifespan <= 0);
		}

		for (auto& component : m_components) {
			if (component->active)	component->Update(deltaTime);
		}


	}

	void Actor::Draw(Renderer& renderer) const {
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
	float Actor::GetRadius()
	{
		return (m_texture) ? m_texture->GetSize().length() * 0.5f * transform.scale * 0.9f : 0;
	}

	void Actor::AddComponent(std::unique_ptr<Component> component)
	{
		component->owner = this;
		m_components.push_back(std::move(component));
	}

	void Actor::Read(const json::value_t& value)
	{
		Object::Read(value);

		JSON_READ(value, tag);
		JSON_READ(value, lifespan);
		JSON_READ(value, persistent);

		if (JSON_HAS(value, transform)) transform.Read(JSON_GET(value, transform));

		//read component
		if (JSON_HAS(value, components)) {
			for (auto& ComponentValue : JSON_GET(value, components).GetArray()) {
				std::string type;
				JSON_READ(ComponentValue, type);

				auto component = Factory::Instance().Create<Component>(type);
				component->Read(ComponentValue);
				AddComponent(std::move(component));
			}
		}
		else
		{
			Logger::Debug("Actor has no components");
		}
		
	
	}
}
