#pragma once
#include "Defines.h"

class Temple
{
private:
	E_PLAYERCOLOR templeColor;

public:
	Temple(E_PLAYERCOLOR _templeColor);

	inline E_PLAYERCOLOR GetColor() const { return templeColor; }
};

