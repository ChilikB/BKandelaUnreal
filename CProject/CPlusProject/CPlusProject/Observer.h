#pragma once

#include "Vector2.h"

class Observer
{
public:
    virtual ~Observer() = default;
    virtual void PositionChanged(const Vector2& value) = 0;
};