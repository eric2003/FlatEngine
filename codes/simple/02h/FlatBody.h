#pragma once
#include "FlatVector.h"

class FlatBody
{
public:
    FlatBody() {}
    ~FlatBody() {}

    void Move(FlatVector amount)
    {
        this->position += amount;
    }

public:
    FlatVector position;
};