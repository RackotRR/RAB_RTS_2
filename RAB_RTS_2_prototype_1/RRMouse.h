#pragma once 
#include "Vector2.h"

enum class MouseButton {
	left,
	middle,
	right
};

enum class MouseState {
	Pressed,
	Released
};

struct RRMouse
{  
	// вызвать перед изменением состояния LeftButton и RightButton
	void SavePrevious() { 
		PrevLeftButton = LeftButton;
		PrevRightButton = RightButton; 
	}

	bool Click(MouseButton button) const {
		if (button == MouseButton::left) {
			return LeftButton == MouseState::Pressed && PrevLeftButton == MouseState::Released;
		}
		else if (button == MouseButton::right) {
			return RightButton == MouseState::Pressed && PrevRightButton == MouseState::Released;
		}
		return false;
	}

	Vector2 Position;
	MouseState LeftButton = MouseState::Released;
	MouseState RightButton = MouseState::Released;
	MouseState PrevLeftButton = MouseState::Released;
	MouseState PrevRightButton = MouseState::Released;
};

