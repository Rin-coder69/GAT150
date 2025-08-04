#pragma once
#include "Math/transform.h"
#include "../Render/Model.h"
#include <memory>
#include <string>
namespace gaia {
	class Actor {
	public:
		std::string name;
		std::string tag;

		vec2 velocity{ 0,0 };
		float damping{ 0.0f };
		bool destroyed{ false };
		float lifespan{ 0 };

		Transform transform;
		class Scene* scene{ nullptr };

		Actor() = default;
		Actor(const Transform& transform, class std:: shared_ptr<Model>model) :
			transform{ transform },
			m_model{model}
		{}

		virtual void Update(float dt);
		virtual void Draw(class Renderer& renderer) const;


		virtual void OnCollision(Actor* other) = 0;
		float GetRadius();

	protected:
		std::shared_ptr<Model> m_model; // Use shared_ptr for better memory management
	};
}