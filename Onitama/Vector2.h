#pragma once
class Vector2 {
public:
	int x, y;
	Vector2();
	Vector2(int _x, int _y);

	Vector2 normalize() const;

	inline Vector2 operator+(const Vector2& B) const { return Vector2(x + B.x, y + B.y); }
	inline bool operator!= (const Vector2& B) const { return !(*this == B); }
	inline bool operator== (const Vector2& B) const { return x == B.x && y == B.y; }
	inline Vector2 operator-(const Vector2& B) const { return Vector2(x - B.x, y - B.y); }
	inline Vector2 operator-() {
		this->x = -this->x;
		this->y = -this->y;
		return *this;
	}
	inline Vector2 operator* (const int B) {
		this->x = this->x * B;
		this->y = this->y * B;
		return *this;
	}
};
