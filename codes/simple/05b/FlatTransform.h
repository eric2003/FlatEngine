#pragma once
#include "FlatVector.h"

class FlatTransform
{
public:
    FlatTransform( const FlatVector & position, float angle );
    FlatTransform( float x, float y, float angle );
    ~FlatTransform() {}
    static FlatTransform Zero()
    {
        return FlatTransform( 0.0f, 0.0f, 0.0f );
    }
public:
    float positionX;
    float positionY;
    float sina;
    float cosa;

};