#pragma once
#include "Object.h"
#include "Components/Component.h"
#include "Math/transform.h"
#include "../Render/Model.h"
#include "../Render/Texture.h"
#include <memory>
#include <string>
#include "Components/RendererComponents.h"
#include "Engineminimal.h"
#include <vector>
namespace gaia {
	class Actor : public Object {
	public:
		std::string tag;
		bool destroyed{ false };
		float lifespan{ 0 };
		bool persistent{ false };

		Transform transform;
		class Scene* scene{ nullptr };
	public:
		Actor() = default;
		Actor(const Transform& transform) :
			transform{ transform }
		{}
		Actor(const Actor& other);


		Class_PROTOTYPE(Actor)
	

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer) const;
		void Read(const json::value_t& value) override;


		virtual void OnCollision(Actor* other) {};
		float GetRadius();

		void AddComponent(std::unique_ptr<Component> component);
		template <typename T>
		T* GetComponent();

		template <typename T>
		std::vector<T*> GetComponents();



	protected:
		std::vector < std::unique_ptr <Component>> m_components;
		res_t<Texture> m_texture;
		//std::shared_ptr<Model> m_model; // Use shared_ptr for better memory management
	};
	template<typename T>
	inline T* Actor::GetComponent()
	{
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				return result;
			}
		}
		return nullptr;
	}

	template<typename T>
	inline std::vector<T*> Actor::GetComponents()
	{
		std::vector<T*> results;
		for (auto& component : m_components) {
			auto result = dynamic_cast<T*>(component.get());
			if (result) {
				results.push_back(result);
			}
		}
		return results;
	}
}


