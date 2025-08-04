#pragma once
#include "../Math/vector2.h"
#include "../Math/vector3.h"
#include "../Core/StringHelper.h"
#include <list>
#include <vector>
#include <memory>
#include <string>
#include "Actor.h"

namespace gaia {
	class Actor;
	class Game;
	class Scene {
	public:

		Scene(Game* game) : m_game{ game } {}
			// Constructor that initializes the scene with a reference to the game
		

		//Scene(Game* game) : m_game{ game }{};

		void Update(float deltaTime);
		void Draw(class Renderer& renderer);

		void AddActor(std::unique_ptr<Actor> actor);
		void RemoveAllActors();

		template<typename T = Actor>
		T* GetActorByName(const std::string& name);

		template<typename T = Actor>
		std::vector<T*> GetActorsByTag(const std::string& tag);

		class Game* GetGame() { return m_game; }

	private:
		class Game* m_game{ nullptr };
		std::list<std::unique_ptr<Actor>> m_actors;

	};

	template<typename T>
	inline T* Scene::GetActorByName(const std::string& name)
	{
		for (auto& actor : m_actors) {
			if (gaia::tolower(actor->name) == gaia::tolower(name)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					return object;
				}
			}
		}
		return nullptr;
	}
	template<typename T>
	inline std::vector<T*> Scene::GetActorsByTag(const std::string& tag)
	{
		std::vector<T*> results;
		Actor* Scene::GetActorByName(const std::string & tag);
		for (auto& actor : m_actors) {
			if (gaia::tolower(actor->tag) == gaia::tolower(tag)) {
				T* object = dynamic_cast<T*>(actor.get());
				if (object) {
					results.push_back(object);
				}
			}
		}
		return results;
	};
}