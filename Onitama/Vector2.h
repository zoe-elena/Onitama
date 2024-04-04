#pragma once
class Vector2
{
public:
	int x = 0;
	int y = 0;
	Vector2() = default;
	Vector2(int _x, int _y);

	Vector2 operator+(const Vector2& B) const { return Vector2(x + B.x, y + B.y); }
	bool operator!= (const Vector2& B) const { return !(*this == B); }
	bool operator== (const Vector2& B) const { return x == B.x && y == B.y; }
	Vector2 operator-(const Vector2& B) const { return Vector2(x - B.x, y - B.y); }
	Vector2 operator-() {
		this->x = -this->x;
		this->y = -this->y;
		return *this;
	}
	Vector2 operator* (const Vector2& B) {
		this->x = this->x * B.x;
		this->y = this->y * B.y;
		return *this;
	}
	Vector2 operator* (const int B) {
		this->x = this->x * B;
		this->y = this->y * B;
		return *this;
	}
};
