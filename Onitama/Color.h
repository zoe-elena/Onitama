#pragma once
class Color
{
public:
	char r, g, b, a;
	static const Color White() { return Color(255, 255, 255, 255); };
	static const Color Black() { return Color(0, 0, 0, 255); };
	static const Color Red() { return Color(255, 0, 0, 255); };
	static const Color Green() { return Color(0, 255, 0, 255); };
	static const Color Blue() { return Color(0, 0, 255, 255); };

	Color();
	Color(int _r, int _g, int _b, int _a);
	Color(int _r, int _g, int _b);
};
