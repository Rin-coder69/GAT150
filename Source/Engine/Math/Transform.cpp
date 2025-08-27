#include "EnginePCH.h"

namespace gaia{
	void Transform::Read(const json::value_t& value) {
		JSON_READ(value, position);
		JSON_READ(value, scale);
		JSON_READ(value, rotation);
	}

}
