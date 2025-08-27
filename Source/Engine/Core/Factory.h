#pragma once
#include "Framework/Object.h"
#include "StringHelper.h"
#include "Singleton.h"
#include "Logger.h"	
#include <map>
#include <memory>
#include <string>
#define FACTORY_REGISTER(classname)\
class Register##classname{\
public:\
	Register##classname() {\
		gaia::Factory::Instance().Register<classname>(#classname);\
	}\
};\
Register##classname register_instance;



namespace gaia
{
	class CreatorBase {
	public:
	virtual ~CreatorBase() = default;
	virtual std::unique_ptr<Object> Create() = 0;

	};
	template<typename T>
		requires std::derived_from<T, Object>
	class ProtoTypeCreator : public CreatorBase {
	public:
		ProtoTypeCreator(std::make_unique<T> prototype):
			m_prototype{ std::move(prototype) }
		{ }
		std::unique_ptr<Object> Create() override {
			return m_prototype->Clone();
		}

	private:
		std::unique_ptr<T> m_prototype;

	};

	class Factory : public Singleton<Factory> {
	public:
		template<typename T>
		requires std::derived_from<T, Object>
		void Register(const std::string& name);

		template<typename T>
			requires std::derived_from<T, Object>
		void RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype);

		template<typename T = Object>
		requires std::derived_from<T, Object>
		std::unique_ptr<T> Create(const std::string& name);
	private:
		std::map<std::string, std::unique_ptr<CreatorBase>> m_registry;

	};

	template<typename T>
	requires std::derived_from<T, Object>
	inline void Factory::Register(const std::string& name)
	{
		std::string key = tolower(name);
		m_registry[key] = std::make_unique<Creator<T>>();

		Logger::Info("added to Factory: {}", name);
	}


	template<typename T>
		requires std::derived_from<T, Object>
	inline void Factory::RegisterPrototype(const std::string& name, std::unique_ptr<T> prototype)
	{
		m_registry[key] = std::make_unique<ProtoTypeCreator<T>>(std::move(prototype));
	}



	template<typename T>
	requires std::derived_from<T, Object>
	inline std::unique_ptr<T> Factory::Create(const std::string& name)
	{
		//make case-insensitive(lowercase)
		std::string key = tolower(name);

		//look for creator in registry
		auto it = m_registry.find(key);
		if (it != m_registry.end()) {
			//found creator, create object
			auto object = it->second->Create();
			T* derived = dynamic_cast<T*>(object.get());
			if (derived) {
				object.release();
				return std::unique_ptr<T>(derived);
			}
			Logger::Error("Type Mismatch of factory object: {}", name);
				//return it->second->Create();
		}
		else {
			Logger::Error("Could not create factory object: {}", name);
		}
		return nullptr;
		//return m_registry[key]->Create();
	}
}