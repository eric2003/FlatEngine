#pragma once
#include "FlatVector.h"
#include <vector>

class FlatMath
{
public:
    FlatMath() = default;
    ~FlatMath() = default;
public:
    static float Dot(FlatVector a, FlatVector b)
    {
        return a.x * b.x + a.y * b.y;
    }

};