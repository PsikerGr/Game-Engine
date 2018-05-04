#pragma once
#include <cstdint>

enum E_EventType : uint8_t
{
	Closed = 0, Resized, LostFocus, GainedFocus,
	TextEntered, KeyPressed, KeyReleased, MouseWheelMoved,
	MouseWheelScrolled, MouseButtonPressed, MouseButtonReleased, MouseMoved,
	MouseEntered, MouseLeft, JoystickButtonPressed, JoystickButtonReleased,
	JoystickMoved, JoystickConnected, JoystickDisconnected, TouchBegan,
	TouchMoved, TouchEnded, SensorChanged, Count
};