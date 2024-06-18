#pragma once
#include "FlatVector.h"

class Collisions
{
public:
    Collisions();
public:
    static float Distance( const FlatVector &centerA, const FlatVector &centerB)
    {
        float dx =  centerA.x - centerB.x;
        float dy =  centerA.y - centerB.y;
        return sqrt(dx*dx + dy*dy);
    }

    static bool IntersectCircles( const FlatVector &centerA, float radisuA,  const FlatVector &centerB, float radisuB,
                          FlatVector &normal, float &depth )
    {
        float distance = Collisions::Distance(centerA,centerB);
        float radii = radisuA + radisuB;

        if( distance >= radii )
        {
            normal = FlatVector::Zero();
            depth = 0.0f;
            return false;
        }

        normal = centerB - centerA;
        normal.normalize();
        depth = radii - distance;
        return true;
    }
};

