#pragma once
#include <iostream>
#include "Observer.h"
#include "Utils.h"

class PlayerCharacterObserver : public Observer
{
public:

	void PositionChanged(const Vector2& value) override
    {
        Utils::SetConsoleColor(6, 0);
        std::cout << "OBSERVER: New character position changed to: " << "x = " << value.x << ", y = " << value.y << std::endl;
		Utils::ResetConsoleColor();
    }
};