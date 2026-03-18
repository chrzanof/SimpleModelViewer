#include "Input.h"

float MouseInput::s_OffsetX = 0.0f;
float MouseInput::s_OffsetY = 0.0f;

bool MouseInput::s_LeftButtonClicked = false;
bool MouseInput::s_RightButtonClicked = false;

Vector2f MouseInput::s_Position = { 0.0f, 0.0f };
Vector2f MouseInput::s_LastPosition = { 0.0f, 0.0f };