#include "InputSystem.h"
#include <SDL3/SDL.h>

namespace gaia {
	bool InputSystem::Initialize() {
		int numKeys;
		const bool* keyboardState = SDL_GetKeyboardState(&numKeys);

		m_keyboardState.resize(numKeys);

		std::copy(keyboardState, keyboardState + numKeys, m_keyboardState.begin());
		m_prevKeyboardState = m_keyboardState;

		SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_prevMousePosition = m_mousePosition;
		
		return true;
	}

	void InputSystem::ShutDown() {

	}

	void InputSystem::Update() {
		m_prevKeyboardState = m_keyboardState;
		const bool* keyboardState = SDL_GetKeyboardState(nullptr);
		std::copy(keyboardState, keyboardState + m_keyboardState.size(), m_keyboardState.begin());

		//mouse state
		m_prevMouseButtonState = m_mouseButtonState;
		uint32_t mouseButtonState = SDL_GetMouseState(&m_mousePosition.x, &m_mousePosition.y);
		m_prevMouseButtonState = this->m_mouseButtonState;
		this->m_mouseButtonState[(uint8_t)MouseButton::LEFT] = (mouseButtonState & SDL_BUTTON_LMASK);
		this->m_mouseButtonState[(uint8_t)MouseButton::MIDDLE] = (mouseButtonState & SDL_BUTTON_MMASK);
		this->m_mouseButtonState[(uint8_t)MouseButton::RIGHT] = (mouseButtonState & SDL_BUTTON_RMASK);
	}
}