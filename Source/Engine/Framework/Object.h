#pragma once

namespace gaia {
	class Object {
	public:
		std::string name;
		bool active{ false };

	public:
		Object() = default;
		virtual ~Object() = default;
	};
}