#pragma once
#include "SDL.h"

class Color
{
public:
	Uint8 r = 0;
	Uint8 g = 0;
	Uint8 b = 0;
	Uint8 a = 0;

	Color() = default;
	Color(Uint8 _r, Uint8 _g, Uint8 _b);

	static const Color White() { return Color(255, 255, 255); };
	static const Color Black() { return Color(0, 0, 0); };
};
