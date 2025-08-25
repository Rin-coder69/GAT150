#include "Scene.h"
#include "../Render/Renderer.h"
#include "../Components/ColliderComponents.h"
#include "../Components/CircleCollider2d.h"

namespace gaia {
	/// <summary>
	/// Updates all actors in the scene by advancing their state based on the elapsed time.
	/// </summary>
	/// <param name="deltaTime">The time elapsed since the last update, in seconds.</param>
	void Scene::Update(float deltaTime) {
		for (auto& actor : m_actors) {
			actor->Update(deltaTime);
		}
		for (auto iter = m_actors.begin(); iter != m_actors.end();) {
			if ((*iter)->destroyed) {
				iter = m_actors.erase(iter);
			}
			else {
				iter++;
			}
		}

		for (auto& actorA : m_actors) {
			for (auto& actorB : m_actors) {
				if (actorA == actorB || (actorA->destroyed || actorB->destroyed)) continue;


				auto colliderA = actorA->GetComponent<ColliderComponent>();
				auto colliderB = actorB->GetComponent<ColliderComponent>();

				if (!colliderA || !colliderB) continue;
				if (colliderA->CheckCollision(*colliderB)) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}

				float distance = (actorA->transform.position - actorB->transform.position).length();
				if (distance <= actorA->GetRadius() + actorB->GetRadius()) {
					actorA->OnCollision(actorB.get());
					actorB->OnCollision(actorA.get());
				}
			}
		}
	}

	/// <summary>
	/// Draws all actors in the scene using the specified renderer.
	/// </summary>
	/// <param name="renderer">The renderer used to draw the actors.</param>
	void Scene::Draw(class Renderer& renderer) {
		for (auto& actor : m_actors) {
			actor->Draw(renderer);
		}
	}

	/// <summary>
	/// Adds an actor to the scene by transferring ownership of the actor to the scene.
	/// </summary>
	/// <param name="actor">A unique pointer to the actor to be added. Ownership of the actor is transferred to the scene.</param>
	void Scene::AddActor(std::unique_ptr<Actor> actor) {
		actor->scene = this;

		m_actors.push_back(std::move(actor));
	}
	void Scene::RemoveAllActors()
	{
		m_actors.clear();
	}

	/*void Scene::Read(const json::value_t& value) {
		for (auto& actorValue : value["actors"].GetArray()) {
			auto actor = Factory::Instance().Create<Actor>("Actor");
			actor->Read(actorValue);

			AddActor(std::move(actor));
		}
	}*/
}

