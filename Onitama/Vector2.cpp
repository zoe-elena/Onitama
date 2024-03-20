#include "Vector2.h"
#include<cmath>

Vector2::Vector2()
{
	Vector2(0, 0);
}

Vector2::Vector2(int _x, int _y) : x(_x), y(_y)
{
}

//	returns ROUNDED normalized Vector2
Vector2 Vector2::normalize() const {
	float tempLength = sqrt(this->x * this->x + this->y * this->y);
	float TempX = floor((float)this->x / tempLength);
	float TempY = floor((float)this->y / tempLength);
	Vector2 temp = Vector2(round((float)this->x / tempLength), round((float)this->y / tempLength));
	return temp;
}