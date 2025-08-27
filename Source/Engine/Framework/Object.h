#pragma once
#include <string>
#include "Core/serializable.h"

namespace gaia {
	class Object : public Serializable {
	public:
		std::string name;
		bool active{ true };

	public:
		Object() = default;
		virtual ~Object() = default;

		// Inherited via Serializable
		virtual void Read(const json::value_t& value) override;
	};
}