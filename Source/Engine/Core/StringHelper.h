#pragma once
#include <string>

namespace gaia {

	/// <summary>
	/// Converts all characters in a string to uppercase.
	/// </summary>
	/// <param name="str">The input string to convert.</param>
	/// <returns>A new string with all characters converted to uppercase.</returns>
	inline std::string tolower(const std::string& str) {
		std::string lowerStr = str;
		for (char& c : lowerStr) {
			c = std::tolower(c);
		}
		return lowerStr;
	}
}