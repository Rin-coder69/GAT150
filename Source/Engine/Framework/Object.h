#pragma once
#include <string>
#include "Core/serializable.h"

#define Class_PROTOTYPE(classname) virtual std::unique_ptr<Object> Clone() { return std::make_unique<classname>(*this); }
\

namespace gaia {
	class Object : public Serializable {
	public:
		std::string name;
		bool active{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		virtual std::unique_ptr<Object> Clone()  = 0;
		// Inherited via Serializable
		virtual void Read(const json::value_t& value) override;
	};
}