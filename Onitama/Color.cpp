#include "Color.h"

Color::Color()
{
	r = g = b = a = 0;
}

Color::Color(int _r, int _g, int _b) : r(_r), g(_g), b(_b) , a(255)
{
}