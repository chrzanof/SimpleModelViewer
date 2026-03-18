#pragma once
#include "math/Vector2f.h"

struct MouseInput
{
	static float s_OffsetX;
	static float s_OffsetY;

	static bool s_LeftButtonClicked;
	static bool s_RightButtonClicked;

	static Vector2f s_Position;
	static Vector2f s_LastPosition;
};