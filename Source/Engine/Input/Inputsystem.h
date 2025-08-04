#pragma once
#include "../Math/vector2.h"
#include <vector>
#include <array>

namespace gaia {
	class InputSystem {
	public:
		enum class MouseButton {
			LEFT = 0,
			MIDDLE = 1,
			RIGHT = 2
		};

	public:
		InputSystem() = default;

		bool Initialize();
		void ShutDown();
		void Update();

		// KEYBOARD INPUT
		bool GetKeyDown(uint8_t key) const { return m_keyboardState[key]; }
		bool GetPreviousKeyDown(uint8_t key) const { return m_prevKeyboardState[key]; }
		bool GetKeyPressed(uint8_t key) const { return !m_prevKeyboardState[key] && m_keyboardState[key]; }
		bool GetKeyReleased(uint8_t key) const { return m_prevKeyboardState[key] && !m_keyboardState[key]; }

		// MOUSE INPUT
		bool GetMouseButtonDown(MouseButton button) { return m_mouseButtonState[(uint8_t)button]; }
		bool GetPreviousMouseButtonDown(MouseButton button) { return m_prevMouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonPressed(MouseButton button) { return !m_prevMouseButtonState[(uint8_t)button] && m_mouseButtonState[(uint8_t)button]; }
		bool GetMouseButtonReleased(MouseButton button) { return m_prevMouseButtonState[(uint8_t)button] && !m_mouseButtonState[(uint8_t)button]; }

		vec2 GetMousePosition() const { return m_mousePosition; }
		vec2 GetPreviousMousePosition() const { return m_prevMousePosition; }

	private:
		vec2 m_mousePosition{ 0, 0 };
		vec2 m_prevMousePosition{ 0, 0 };

		std::vector<bool> m_keyboardState;
		std::vector<bool> m_prevKeyboardState;

		std::array<bool, 3> m_mouseButtonState{ false, false, false }; // Array for mouse button states
		std::array<bool, 3> m_prevMouseButtonState{ false, false, false }; // Array for previous mouse button states
	};
}
